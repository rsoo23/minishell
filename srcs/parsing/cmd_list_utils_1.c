/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:48:43 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/08 13:06:09 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_cmd(int pipe_stat)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmds = NULL;
	new_cmd->infile_name = NULL;
	new_cmd->fd_in = 0;
	new_cmd->fd_out = 1;
	new_cmd->pipe_stat = pipe_stat;
	if (pipe_stat == 1)
	{
		if (pipe(new_cmd->pipe) == -1)
		{
			free(new_cmd);
			return (NULL);
		}
	}
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

t_cmd	*find_last_cmd(t_cmd *cmd_list)
{
	t_cmd	*temp;

	if (!cmd_list)
		return (NULL);
	temp = cmd_list;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	add_cmd_to_back(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*last_cmd;

	if (!new_cmd)
		return ;
	if (!cmd_list || !(*cmd_list))
		*cmd_list = new_cmd;
	else
	{
		last_cmd = find_last_cmd(*cmd_list);
		last_cmd->next = new_cmd;
		new_cmd->prev = last_cmd;
	}
}

// void	clear_cmds(t_cmd **cmd_list)
// {
// 	t_cmd   *temp;

// 	if (!cmd_list || !*cmd_list)
// 		return ;
// 	temp = *cmd_list;
// 	while (*cmd_list)
// 	{
// 		temp = *cmd_list;
// 		*cmd_list = (*cmd_list)->next;
// 		free(temp->str);
// 		free(temp);
// 	}
// 	*cmd_list = NULL;
// }
