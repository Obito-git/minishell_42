/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:09:47 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 15:09:47 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	invalid_var_id(char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (true);
	str++;
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (true);
		str++;
	}
	return (false);
}

static void	remove_var(char *full_var, t_strlist *env)
{
	t_strlist	var_list;
	size_t		stem_len;
	char		*equal;

	var_list = *env;
	equal = ft_strchr(full_var, '=');
	if (equal == NULL)
		return ;
	equal++;
	stem_len = equal - full_var;
	while (var_list.size--)
	{
		if (ft_strncmp(var_list.head->str, full_var, stem_len) == 0)
		{
			remove_node_from_strlist(env, var_list.head);
			break ;
		}
		var_list.head = var_list.head->next;
	}
}

int	xport(t_command *cmd, t_strlist *envlist)
{
	char	**args;
	int		i;

	args = cmd->args;
	i = 1;
	if (args[i] == NULL)
		return (env(cmd, envlist));
	while (args[i])
	{
		if (invalid_var_id(args[i]))
		{
			ft_dprintf_str(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n",
				args[i]);
		}
		else if (ft_strchr(args[i], '='))
		{
			remove_var(args[i], envlist);
			append_str_to_strlist(envlist, args[i]);
		}
		i++;
	}
	return (update_strlist_strarr_value(envlist));
}
