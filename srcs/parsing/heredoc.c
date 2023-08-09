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
	char	*user_in;
	char	*temp;

	user_in = readline("> ");
	close(hd_pipe[0]);
	while (user_in && ft_strncmp(user_in, limiter, ft_strlen(user_in)))
	{
		free(user_in);
		user_in = readline("> ");
		temp = ft_strjoin(user_in, "\n");
		write(hd_pipe[1], temp, ft_strlen(temp));
		free(temp);
	}
	free(user_in);
	exit(EXIT_SUCCESS);
}

void	get_heredoc(t_cmd *new_cmd, char *limiter)
{
	int		hd_pipe[2];
	pid_t	pid;

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
