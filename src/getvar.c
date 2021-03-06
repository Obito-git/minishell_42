/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:08:51 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:08:51 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var_start(char *var, char **envp)
{
	int	vlen;

	var++;
	vlen = ft_strlen(var);
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0
				&& *(*envp + vlen) == '=' )
			{
				return (*envp);
			}
			envp++;
		}
	}
	return (NULL);
}

char	*get_env_var_val(char *var, char **envp)
{
	int	vlen;

	var++;
	vlen = ft_strlen(var);
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0
				&& *(*envp + vlen) == '=' )
			{
				return (*envp + vlen + 1);
			}
			envp++;
		}
	}
	return (NULL);
}

char	*get_env_var_val_from_slice(char *var, char *var_end, t_strlist *env)
{
	int		vlen;
	char	**envp;

	if (var && *var != '$')
		return (NULL);
	var++;
	if (ft_strncmp("?", var, 1) == 0)
		return (ft_itoa(env->ret));
	envp = env->strarr_value;
	vlen = var_end - var;
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0
				&& *(*envp + vlen) == '=' )
				return (ft_strdup(*envp + vlen + 1));
			envp++;
		}
	}
	return (NULL);
}
