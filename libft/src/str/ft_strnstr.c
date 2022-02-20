/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:34:24 by sloquet           #+#    #+#             */
/*   Updated: 2022/01/29 15:09:20 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_str.h"

/**
 * ft_strnstr locates the first occurrence of the null-terminated string sub
 * in the string big, where not more than len characters are searched.
 * Characters that appear after a `\0' character are not searched.
 * 
 * RETURN VALUES
 * > If sub is an empty string, big is returned;
 * > If sub occurs nowhere in big, NULL is returned;
 * > Otherwise a ptr to the 1st char of the 1st occurrence of sub is returned.
 */

char	*ft_strnstr(const char *big, const char *sub, size_t len)
{
	size_t	i;
	size_t	k;

	if (!sub[0])
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		k = 0;
		while (sub[k] == big[i + k] && i + k < len)
		{
			k++;
			if (!sub[k])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <bsd/string.h>
#include <stdio.h>

static int	ft_test(const char *big, const char *sub, size_t len)
{
	char	*std_result;
	char	*ft_result;

	std_result = strnstr(big, sub, len);
	ft_result = ft_strnstr(big, sub, len);
	return (std_result == ft_result);
}

int	main(void)
{
	if (!ft_test("", "", 0)
		|| !ft_test("", "", 10)
		|| !ft_test("Haystack", "Needle", 1)
		|| !ft_test("Haystack", "Haystack", 100)
		|| !ft_test("NeedleNeedle", "NeedleNeedle", 7)
		|| !ft_test("Haystack", "", 9)
		|| !ft_test("", "Needle", 5)
		|| !ft_test("qwertyuiopasdfghjkl", "iopa", 9)
		|| !ft_test("qwertyuiopasdfghjkl", "iopa", 11)
		|| !ft_test("qwertyuiopasdfghjkl", "iopa", 19))
	{
		ft_printf("KO: ft_strnstr\n");
		return (1);
	}
	ft_printf("OK: ft_strnstr\n");
}
*/
