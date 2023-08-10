/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:58:30 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/10 11:29:16 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	finishing_up_cmd(int child_amount, t_cmd *cmd_list)
{
	int	sig;

	if (cmd_list)
		closing_pipes(cmd_list, NULL);
	while (child_amount--)
	{
		wait(&sig);
		if (WIFEXITED(sig))
			g_main.exit_code = WEXITSTATUS(sig);
	}
	sig_init_or_end(1);
}

void	print_exit_error_msg(char *str, int type)
{
	ft_putstr_fd("minishell:\033[0;31m exit\033[0;37m: ", 2);
	if (type == 1)
		ft_putstr_fd("too many argument\n", 2);
	if (type == 2)
	{	
		ft_putstr_fd("\033[0;31m", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\033[0;37m: numeric argument required\n", 2);
	}
}

void	child_init(t_cmd *cmd_node)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	closing_pipes(cmd_node, cmd_node);
	dup2(cmd_node->fd_in, STDIN_FILENO);
	if (cmd_node->fd_in != 0)
		close(cmd_node->fd_in);
	dup2(cmd_node->fd_out, STDOUT_FILENO);
	if (cmd_node->fd_out != 1)
		close(cmd_node->fd_out);
}

int	exit_func1(char **cmds, int cmdlstlen, int type)
{
	if (type == 0)
	{
		print_exit_error_msg(cmds[1], 2);
		if (cmdlstlen == 1)
		{
			g_main.exit_code_minishell = 255;
			return (EXIT_SHELL);
		}
		return (ACTION_BUILTIN);
	}
	else if (type == 1)
	{
		g_main.exit_code = 1;
		print_exit_error_msg(NULL, 1);
		return (ACTION_BUILTIN);
	}
	else if (type == 2)
	{
		g_main.exit_code_minishell = 0;
		return (EXIT_SHELL);
	}
	return (0);
}

int	exit_func(char **cmds, int cmdlstlen)
{
	int	i;

	i = -1;
	if (cmds && cmds[1])
	{
		while (cmds[1][++i])
			if (!ft_isdigit(cmds[1][i]))
				break ;
		if (cmds[1][i])
			return (exit_func1(cmds, cmdlstlen, 0));
		if (cmds[2])
			return (exit_func1(cmds, cmdlstlen, 1));
		if (cmdlstlen == 1)
		{
			g_main.exit_code_minishell = ft_atoi(cmds[1]);
			return (EXIT_SHELL);
		}
	}
	if (cmds && cmds[0] && cmdlstlen == 1)
		return (exit_func1(cmds, cmdlstlen, 2));
	return (ACTION_BUILTIN);
}
