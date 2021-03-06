/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_strarray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:47:50 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/07 15:47:50 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//applies ft_strtrim on every string of the array
//if malloc error, all memory will be freed
char	**ft_strtrim_strarray(char **s, char *set)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	if (!s || !set)
		return (NULL);
	while (s[i])
	{
		tmp = ft_strtrim(s[i], set);
		if (!tmp)
		{
			y = 0;
			while (s[y])
				free(s[y++]);
			free(s);
			return (NULL);
		}
		free(s[i]);
		s[i] = tmp;
		i++;
	}
	return (s);
}
