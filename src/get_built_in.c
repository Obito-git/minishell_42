/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:58:04 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:58:04 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const struct {
	char	*name;
	int		(*func)(t_command*, t_strlist *env);
} s_built_in_table[] = {
	{"echo", echo},
	{"cd", cd},
	{"pwd", pwd},
	{"export", xport},
	{"unset", unset},
	{"env", env},
	{"exit", xit},
};

int	(*get_built_in(t_command *cmd))(t_command*a, t_strlist *b)
{
	unsigned long	i;

	i = 0;
	while (i < sizeof(s_built_in_table) / sizeof(s_built_in_table[0])
		&& ft_strncmp(cmd->command,
			s_built_in_table[i].name,
			ft_strlen(cmd->command)))
	{
		i++;
	}
	if (i == sizeof(s_built_in_table) / sizeof(s_built_in_table[0]))
		return (NULL);
	else
		return (s_built_in_table[i].func);
}
