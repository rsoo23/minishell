/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:30:16 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/20 13:30:16 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	infile_to_pipe(t_cmd *cmd)
{
    dup2(cmd->fd_table.infile_fd, STDIN_FILENO);
    close(cmd->fd_table.pipe[i][0]);
    dup2(cmd->fd_table.pipe[i][1], STDOUT_FILENO);
}

void	pipe_to_outfile(t_cmd *cmd)
{
	close(cmd->fd_table.pipe[i - 1][1]);
	dup2(cmd->fd_table.pipe[i - 1][0], STDOUT_FILENO);
	dup2(cmd->fd_table.infile_fd, STDIN_FILENO);
}

void	pipe_to_pipe(t_cmd *cmd)
{
	close(cmd->fd_table.pipe[i - 1][1]);
	dup2(cmd->fd_table.pipe[i - 1][0], STDIN_FILENO);
	close(cmd->fd_table.pipe[i][0]);
	dup2(cmd->fd_table.pipe[i][1], STDOUT_FILENO);
}

