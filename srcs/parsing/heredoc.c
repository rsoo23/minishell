/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:43:35 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/21 21:43:35 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void create_heredoc_cmd(t_cmd **cmd_list, char *limiter)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd();
	new_cmd->redirection = ft_strdup("<<");
	new_cmd->limiter = ft_strjoin(limiter, "\n");
	add_cmd_to_back(cmd_list, new_cmd);
}

static void	create_heredoc_pipe(t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd();
	if (pipe(new_cmd->heredoc_pipe) == -1)
		return ;
	add_cmd_to_back(cmd_list, new_cmd);
}

void	get_heredoc(t_cmd **cmd_list, char *limiter)
{
	if (!limiter)
	{
		printf("<< error\n");
		return ;
	}
	create_heredoc_cmd(cmd_list, limiter);
	create_heredoc_pipe(cmd_list);
}
