#include "minishell.h"

int	env(void *args, t_strlist *env)
{
	(void) args;

	/*char **str;*/

	/*str = env->envp;*/
	/*while (*str)*/
	/*{*/
	/*    printf("%s\n", *str);*/
	/*    str++;*/
	/*}*/

	t_strlist var_list;

	var_list = *env;
	while (var_list.size--)
	{
		printf("%s\n", var_list.head->str);
		var_list.head = var_list.head->next;
	}

	return (0);
}
