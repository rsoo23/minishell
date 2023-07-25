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

static void	heredoc_child(int hd_pipe[2], char *limiter)
{
    char    *temp;

    temp = get_next_line(0);
    close(hd_pipe[0]);
    while (temp && ft_strncmp(temp, limiter, ft_strlen(temp) - 1))
    {
        write(hd_pipe[1], temp, ft_strlen(temp));
        free(temp);
        temp = get_next_line(0);
    }
	exit(EXIT_SUCCESS);
}

void	get_heredoc(t_cmd *new_cmd, char *limiter)
{
	int      hd_pipe[2];
    pid_t    pid;

    if (pipe(hd_pipe) == -1)
        return ;
    pid = fork();
    if (pid == -1)
        return ;
    if (pid == 0)
        heredoc_child(hd_pipe, limiter);
    else
    {
        close(hd_pipe[1]);
		new_cmd->fd_in = hd_pipe[0];
        wait(NULL);
	}
}
