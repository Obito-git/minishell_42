/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*enum e_quote_state {*/
/*    not_in_quote,*/
/*    single_quote,*/
/*    double_quote,*/
/*    fini,*/
/*};*/

static enum e_quote_state	(*g_quote_func_table[])(char *, int*, int**) = {
	&not_in_quote_mode,
	&sq_mode,
	&dq_mode,
};

enum e_quote_state	not_in_quote_mode(char *str, int *i, int **table)
{
	(*i)++;
	*i = next_any_quote(str, *i);
	if (str[*i] == 0)
	{
		log_index(*i, table);
		return (fini);
	}
	log_index(*i, table);
	if (str[*i] == '\'')
		return (single_quote);
	if (str[*i] == '\"')
		return (double_quote);
	return (-1);
}

enum e_quote_state	sq_mode(char *str, int *i, int **table)
{
	(*i)++;
	*i = next_single_quote(str, *i);
	if (str[*i] == 0)
	{
		(*table)--;
		log_index(*i, table);
		return (fini);
	}
	log_index(*i + 1, table);
	if (str[*i + 1] == 0)
		return (fini);
	return (not_in_quote);
}

enum e_quote_state	dq_mode(char *str, int *i, int **table)
{
	(*i)++;
	*i = next_double_quote(str, *i);
	if (str[*i] == 0)
	{
		(*table)--;
		log_index(*i, table);
		return (fini);
	}
	log_index(*i + 1, table);
	if (str[*i + 1] == 0)
		return (fini);
	return (not_in_quote);
}

int	*register_quotes(char *str)
{
	int					*indexes;
	int					*box;
	enum e_quote_state	state;
	int					i;

	indexes = malloc(4096 * sizeof(int));
	if (!indexes || !str)
		return (NULL);
	if (str[0] == '\'')
		state = single_quote;
	else if (str[0] == '\"')
		state = double_quote;
	else
		state = not_in_quote;
	i = 0;
	box = indexes;
	log_index(0, &box);
	while (*str && state != fini)
		state = g_quote_func_table[state](str, &i, &box);
	log_index(0, &box);
	return (indexes);
}
