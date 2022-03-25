#include "minishell.h"

//closes all the tubes of the array list except current.
//used to close the tubes inside the child's process
void	close_extra_tubes(t_command *head, t_command *current)
{
	while (head)
	{
		if (head != current && head->pipe)
		{
			close(head->tube[0]);
			close(head->tube[1]);
		}
		head = head->next;
	}
}

int	try_to_execute(t_command *c, t_strlist *env, int in_fd, int out_fd)
{
	reset_sigquit();
	if (!c->path_to_bin && (!c->prev || (!c->prev->out_mode && !c->prev->in_mode)))
	{
		ft_dprintf_str(STDERR_FILENO, "%s: command not found\n", c->command);
		//if will be in/out troubles need to delete close -_-
		if (in_fd != -1)
			close(in_fd);
		if (out_fd != -1)
			close(out_fd);
		exit(EXIT_UNK_CMD);
	}
	else if (c->path_to_bin && (!c->prev || (!c->prev->out_mode && !c->prev->in_mode)))
		return (execve(c->path_to_bin, c->args, env->envp));
	else if (c->prev && (c->prev->out_mode || c->prev->in_mode))
		return (EXIT_SUCCESS);
	return (EXIT_UNK_CMD);
}

//Tries to execute built-in if possible, if not tries to execute a binary file;
// calls all input/output files and pipe functions
void	exec_com(t_command *head, t_command *c, t_strlist *env)
{
	int		out_fd;
	int		in_fd;
	int		(*built_in)(t_command*, t_strlist*);
	int 	ret;

	ret = 0;
	out_fd = set_out_path(c);
	if (out_fd == -2)
		exit(EXIT_FAILURE);
	in_fd = set_in_path(head, c);
	if (in_fd != -1 && out_fd == -1 && c->next)
		out_fd = set_out_path(c->next);
	set_tubes_path(head, c);
	built_in = get_built_in(c);
	if (built_in)
		ret = built_in(c, env);
	else
		ret = try_to_execute(c, env, in_fd, out_fd);
	if (out_fd != -1)
		close(out_fd);
	if (in_fd != -1)
		close(in_fd);
	free_commands(head);
	exit(ret);
}

/* Creates child processes, calls execution of commands and waits for their execution.
* The main function of the executor
*/
int	execute_pipeline(t_command *head, t_strlist *env)
{
	t_command	*tmp;
	int			pid;
	int			wstatus;
	int			(*built_in)(t_command*, t_strlist*);

	built_in = NULL;
	if (head->next == NULL)
		built_in = get_built_in(head);
	if (built_in)
		return (built_in(head, env));
	pid = -1;
	tmp = head;
	while (pid != 0 && tmp)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork: ");
		else if (pid == 0)
			exec_com(head, tmp, env);
		tmp = tmp->next;
	}
	close_extra_tubes(head, NULL);
	while (waitpid(-1, &wstatus, 0) != -1 || errno != ECHILD)
		;
	return (WEXITSTATUS(wstatus));
}
