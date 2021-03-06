/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:30:58 by amyroshn          #+#    #+#             */
/*   Updated: 2022/04/21 10:31:03 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//close opened fds if possible and frees struct
void	close_fds(t_inout_fd *fds)
{
	if (!fds)
		return ;
	if (fds->in_fd >= 0)
		close(fds->in_fd);
	if (fds->out_fd >= 0)
		close(fds->out_fd);
	free(fds);
}

void	reset_fds(t_inout_fd *fds)
{
	int	in;
	int	out;

	in = fds->in_fd;
	out = fds->out_fd;
	if (fds->out_fd >= 0)
	{
		dup2(fds->backup_out, STDOUT_FILENO);
		close(fds->backup_out);
	}
	if (fds->in_fd >= 0)
	{
		dup2(fds->backup_in, STDIN_FILENO);
		close(fds->backup_in);
	}
}
