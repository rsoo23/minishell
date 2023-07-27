/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:42:09 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/27 00:12:01 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_cmd_list_len(t_cmd *lst)
{
	t_cmd	*temp;
	int		i;

	if (!lst)
		return (0);
	temp = lst;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	init_fds(t_cmd *lst)
{
	t_cmd	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->fd_in == 0 && temp->prev != NULL)
			temp->fd_in = temp->pipe[0];
		if (temp->fd_out == 1 && temp->next != NULL)
			temp->fd_out = temp->next->pipe[1];
		temp = temp->next;
	}
}