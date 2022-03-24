#include "minishell.h"

void command_print(t_command *c)
{
	if (!c)
		printf("Command is null\n");
	else
	{
		while (c)
		{
			int i = 0;
			printf("Command: %s\n", c->command);
			printf("Args: ");
			if (!c->args)
				printf("Args null");
			if (!c->args[i])
				printf("No args");
			while (c->args && c->args[i])
			{
				printf(" [%s] ", c->args[i]);
				i++;
			}
			printf("\nPipe: %s", c->pipe ? "YES\n" : "NO\n");
			if (c->out_mode)
				printf("OUT: %s", c->out_mode == 1 ? "REWRITE\n" : "APPEND\n");
			if (c->in_mode)
				printf("IN: %s", c->in_mode == 1 ? "SOLO\n" : "MULTU\n");
			printf("PATH: %s\n", c->path_to_bin);
			printf("------------------\n");
			c = c->next;
		}
	}
}

/*	parse user input into an array list. save result in head variable
*	call the readline if there is no command after the pipe and
*	correctly displays the history in this case
*/
void	prepare_commands(char *user_input, t_command **head, t_strlist *env)
{
	t_command	*last;
	char		*tmp;
	char		*history;

	history = ft_strdup(user_input);
	*head = parse(user_input, env);
	last = get_last_cmd(*head);
	while (last && last->pipe)
	{
		user_input = readline("> ");
		while (ft_strlen(user_input) == 0)
		{
			free(user_input);
			user_input = readline("> ");
		}
		last->next = parse(user_input, env);
		tmp = ft_str_threejoin(history, " ", user_input);
		free(history);
		free(user_input);
		history = tmp;
		if (last->next)
			last->next->prev = last;
		last = get_last_cmd(*head);
	}
	if (history)
		add_history(history);
	free(history);
}

t_bool	check_args(int ac, char **av, char **envp, t_strlist **env)
{
	if (ac != 1 || !av)
	{
		printf("You can't have args\n");
		return (FALSE);
	}
	*env = make_strlist_from_null_terminated_str_array(envp);
	if (env == NULL)
	{
		perror("Unable to allocate for list of variables");
		return (FALSE);
	}
	printf("\e[1A");
	return (TRUE);
}

int main(int ac, char **av, char **envp)
{
	char        *user_input;
	t_command	*head;
	t_strlist	*env;
	int			ret;

	env = NULL;
	if (!check_args(ac, av, envp, &env))
		return (1);
	while (1)
	{
		head = NULL;
		set_signal_handling();
		user_input = readline(PROMPT);
		if (!user_input)
		{
			ft_dprintf_str(STDERR_FILENO, "exit\n");
			free_strlist(env);
			return (0);
		}
		if (ft_strlen(user_input) && ft_strcmp(user_input, "\n") != 0)
		{

			prepare_commands(user_input, &head, env);
			head = find_syntax_errors(head);
			//command_print(head);
			//head = NULL; //disactivate execution, create a leaks
			free(user_input);
			if (head)
				env->ret = execute_pipeline(head, env);
		}
		else
			free(user_input);
		free_commands(head);
	}
	ret = env->ret;
	free_strlist(env);
	return (ret);
}
