/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:16:05 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:16:05 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <sys/signal.h>
# include "libft.h"
# include "t_strlist.h"
# include "expansion.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define OUT_REWRITE 1
# define OUT_APPEND 2
# define IN_FILE 1
# define IN_HEREDOC 2
# define _GNU_SOURCE 1
# define EXIT_UNK_CMD 127

# define RED   "\e[31m"
# define ENDCOLOR  "\e[0m"
# define PROMPT "\001\e[31m\002minishell$ \001\e[0m\002"

# define ERROR_SYNTAX "syntax error near unexpected token "
# define HEADER "minishell: "
# define ERROR_HEREDOC1 "minishell: warning: here-document at line %d "
# define ERROR_HEREDOC2 "delimited by end-of-file (wanted `%s')\n"

typedef struct sigaction	t_sigaction;

typedef struct s_command
{
	char				*command;
	char				*path_to_bin;
	char				**args;
	bool				to_execute;
	bool				pipe;
	int					*tube;
	struct s_redir		*infile;
	struct s_redir		*outfile;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_redir
{
	char			*filename;
	char			mode;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_inout_fd
{
	int	in_fd;
	int	out_fd;
	int	backup_in;
	int	backup_out;
}	t_inout_fd;

typedef int					(*t_built_in)(t_command*, t_strlist*);

//	struct_utils.c
t_command	*command_init(void);
t_command	*free_commands(t_command *c);
void		delete_com_from_list(t_command **head);
t_command	*get_last_cmd(t_command *head);
//	parsing
bool		is_pipe_redir_char(char c);
char		*find_command(char **envp, t_command *c);
t_command	*parse(char *user_input, t_strlist *env);
int			check_pathname_access(t_command *c, t_strlist *env);
//	str_to_struct.c
t_command	*get_commands_list(char **c, t_strlist *env);
//	executor.c
void		close_extra_tubes(t_command *head, t_command *current);
int			execute_pipeline(t_command *head, t_strlist *env);
//	pipes_redir.c
t_inout_fd	*set_redirections(t_command *c);
void		set_tubes_path(t_command *head, t_command *c);
//	t_fds
void		close_fds(t_inout_fd *fds);
void		reset_fds(t_inout_fd *fds);
//	error_handler.c
t_command	*find_syntax_errors(t_command *head, t_strlist *env);
//	heredoc.c
int			get_heredoc_fd(char *delim, t_command *head,
				t_command *current, t_redir *red);
char		*get_heredoc_tmpname(t_command *head,
				t_command *current, t_redir *redir);
void		delete_tmpfiles(t_command *head);
//	built-ins
t_built_in	get_built_in(t_command *cmd);
int			echo(t_command *cmd, t_strlist *env);
int			pwd(t_command *cmd, t_strlist *env);
int			unset(t_command *cmd, t_strlist *env);
int			xport(t_command *cmd, t_strlist *env);
int			xit(t_command *cmd, t_strlist *env);
int			env(t_command *cmd, t_strlist *env);
int			cd(t_command *cmd, t_strlist *env);
//	env
char		*get_env_var_start(char *var, char **envp);
char		*get_env_var_val(char *var, char **envp);
ssize_t		writevar(int fd, char *var, char **envp);
//	vars
char		*get_env_var_val_from_slice(char *var,
				char *var_end, t_strlist *env);
//	signal handling
void		set_interactive_sigint_handling(void);
void		set_noninteractive_sigint_handling(void);
void		set_sigquit_handling(void);
void		set_signal_handling(void);
void		ignore_sigint(void);
void		ignore_siquit(void);
void		reset_sigint(void);
void		reset_sigquit(void);
void		reset_signals(void);
void		interactive_sigint_handler(int signal);
void		noninteractive_sigint_handler(int signal);
void		sigquit_handler(int signal);
void		set_noninteractive_signal_handling(void);
//	expand API
t_strlist	*expand_pipeline(char *user_input, t_strlist *env);
char		**expand_simple_command(char *simple_command, t_strlist *env);
//	Main functions
void		command_print(t_command *c);
void		prepare_commands(char *in, t_command **head,
				char **h, t_strlist *env);
bool		check_main_args(int ac, char **av, char **envp, t_strlist **env);
void		execute_userinput(t_strlist *env, char *user_input);
//	utils
int			child_status(int wstatus);
bool		is_pipe_redir(char *s);
int			is_directory(const char *path);
bool		contains_only(char *s, char c);
t_command	*free_commands_strlist(t_command *c, t_strlist *l);
//	t_redir
t_redir		*free_redir(t_redir *head);
t_redir		*append_redir(t_redir *head, char *mode, char *name);
#endif
