/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:53:26 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:53:56 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
