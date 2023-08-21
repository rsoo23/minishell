/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:49 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/10 17:50:14 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_error(t_cmd *cmd_lst, int type)
{
	t_cmd	*temp;

	temp = cmd_lst;
	ft_putstr_fd("minishell\033[0;37m: \033[0;31m", 2);
	if (type == 0)
	{
		ft_putstr_fd(cmd_lst->cmds[0], 2);
		ft_putstr_fd("\033[0;37m: command not found\n", 2);
	}
	else
	{
		ft_putstr_fd(cmd_lst->infile_name, 2);
		ft_putstr_fd("\033[0;37m: No such file or directory\n", 2);
	}
	while (temp->prev)
		temp = temp->prev;
	cmd_clear(&temp);
	freeing_2darray(g_main.envp);
	if (type != 0)
		exit(1);
	exit(127);
}

int	exec_action_builtins(char **cmd, int cmdlstlen)
{
	int	i;

	i = 1;
	if (!cmd || !(cmdlstlen >= 1 && cmdlstlen <= 2))
		return (0);
	if (!ft_strncmp(cmd[0], "cd", 3) && cmdlstlen == 1)
		changing_dir(cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6) && array2d_y(cmd) > 1
		&& cmdlstlen == 1)
		while (cmd[i])
			remove_envp(cmd[i++]);
	else if (!ft_strncmp(cmd[0], "export", 7) && array2d_y(cmd) > 1
		&& cmdlstlen == 1)
		while (cmd[i])
			add_to_envp(cmd[i++]);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		return (exit_func(cmd, cmdlstlen));
	else
		return (0);
	return (ACTION_BUILTIN);
}

// used to execute display builtins like pwd for path or env for envp
int	exec_display_builtins(char **cmd)
{
	if (cmd && !ft_strncmp(cmd[0], "pwd", 4))
		printf("%s\n", g_main.current_path);
	else if (cmd && !ft_strncmp(cmd[0], "env", 4))
	{
		if (cmd[1])
		{
			ft_putstr_fd("minishell\033[0;37m: env: \033[0;31m", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd("\033[0;37m: No such file or directory\n", 2);
			return (DISPLAY_BUILTIN);
		}
		print_envp();
	}
	else if (cmd && !ft_strncmp(cmd[0], "echo", 5))
		shell_echo(cmd);
	else if (cmd && !ft_strncmp(cmd[0], "export", 7) && !cmd[1])
		print_export();
	else
		return (0);
	return (DISPLAY_BUILTIN);
}

// --------- USED FOR DEBUGGING ---------
// | ft_putstr_fd("in  fd ", 2);
// | ft_putnbr_fd(cmd_list->fd_in, 2);
// | ft_putchar_fd('\n', 2);		
// | ft_putstr_fd("out fd ", 2);	
// | ft_putnbr_fd(cmd_list->fd_out, 2);
// | ft_putchar_fd('\n', 2);		
// --------------\/----------------------
void	execute_child(t_cmd *cmd_node)
{
	pid_t	pid;
	char	*temp;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		child_init(cmd_node);
		if (exec_display_builtins(cmd_node->cmds) == DISPLAY_BUILTIN)
			exit(EXIT_SUCCESS);
		if (cmd_node->fd_in == -1 || cmd_node->fd_out == -1)
			cmd_error(cmd_node, 1);
		if (!cmd_node->cmds)
			exit(EXIT_SUCCESS);
		execve(cmd_node->cmds[0], cmd_node->cmds, g_main.envp);
		temp = merge_path(ft_strjoin("/", cmd_node->cmds[0]));
		execve(temp, cmd_node->cmds, g_main.envp);
		cmd_error(cmd_node, 0);
	}
}

int	execute(t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		exit_status;
	int		child_index;

	init_fds(cmd_list);
	temp = cmd_list;
	exit_status = 0;
	child_index = 1;
	sig_init_or_end(0);
	while (temp && child_index++)
	{
		exit_status = exec_action_builtins(temp->cmds, getcmdlstlen(cmd_list));
		if (exit_status == ACTION_BUILTIN)
		{
			temp = temp->next;
			continue ;
		}
		if (exit_status == EXIT_SHELL)
			break ;
		if (exit_status == 0 || getcmdlstlen(cmd_list) > 1)
			execute_child(temp);
		temp = temp->next;
	}
	finishing_up_cmd(--child_index, cmd_list);
	return (exit_status);
}
