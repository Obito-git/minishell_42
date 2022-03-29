/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:29:18 by tpouget           #+#    #+#             */
/*   Updated: 2022/03/27 15:29:18 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/* This function will always null terminate past n bytes so make sure you
 * allocate for the null byte at the end or it will overflow 				*/
char	*ft_strcat_slice(char *dest, const char *src, int n)
{
	size_t		i;
	size_t		y;
	const char	*end;

	if (dest && src && n > 0)
	{
		i = 0;
		y = ft_strlen(dest);
		end = src + n;
		while (src[i] && &src[i] != end)
		{
			dest[y] = src[i];
			i++;
			y++;
		}
		dest[y] = '\0';
	}
	return (dest);
}