/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:42:09 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/10 11:13:42 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	getcmdlstlen(t_cmd *lst)
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
		if (temp->fd_in == 0 && temp->prev != NULL && temp->pipe_stat == 1)
			temp->fd_in = temp->pipe[0];
		if (temp->fd_out == 1 && temp->next != NULL)
			temp->fd_out = temp->next->pipe[1];
		temp = temp->next;
	}
}

// takes in the entire list and a node for ref
// if it detects the node it will close the correct in's and out
// else it will close the pipes
void	closing_pipes(t_cmd *cmd_list, t_cmd *cmd_node)
{
	t_cmd	*temp;

	temp = cmd_list;
	while (temp->prev)
		temp = temp->prev;
	while (temp)
	{
		if (temp == cmd_node)
		{
			close(temp->pipe[1]);
			if (temp->next)
			{
				temp = temp->next;
				close(temp->pipe[0]);
			}
			temp = temp->next;
			continue ;
		}
		if (temp->pipe_stat)
		{
			close(temp->pipe[0]);
			close(temp->pipe[1]);
		}
		temp = temp->next;
	}
}

void	sig_handler_child(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_main.exit_code = 131;
	}
	else
	{
		ft_putchar_fd('\n', 2);
		g_main.exit_code = 130;
	}
}

void	sig_init_or_end(int type)
{
	if (type == 0)
	{
		g_main.new_attri.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &g_main.new_attri);
		signal(SIGQUIT, sig_handler_child);
		signal(SIGINT, sig_handler_child);
	}
	else
	{
		g_main.new_attri.c_lflag &= ~(ECHOCTL);
		tcsetattr(0, TCSANOW, &g_main.new_attri);
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
	}
}
