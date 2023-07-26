/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:49 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/26 17:16:50 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_temp(void)
{
	printf("Error: cmd not found\n");
	exit(EXIT_FAILURE);
}

void	execute_child(t_cmd *cmd_list)
{
	pid_t	pid;
	char	*temp;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		// ft_putstr_fd("in  fd ", 2);
		// ft_putnbr_fd(cmd_list->fd_in, 2);
		// ft_putchar_fd('\n', 2);
		// ft_putstr_fd("out fd ", 2);
		// ft_putnbr_fd(cmd_list->fd_out, 2);
		// ft_putchar_fd('\n', 2);
		if (cmd_list->fd_in != 0)
			dup2(cmd_list->fd_in, STDIN_FILENO);
		if (cmd_list->fd_out != 1)
			dup2(cmd_list->fd_out, STDOUT_FILENO);
		if (cmd_list->next != NULL)
			close(cmd_list->next->pipe[0]);
		temp = merge_path(ft_strjoin("/", cmd_list->cmds[0]));
		execve(temp, cmd_list->cmds, g_main.envp);
		error_temp();
	}
	else
		if (cmd_list->next != NULL)
			close(cmd_list->next->pipe[1]);
}

int	execute_builtins1(char **cmd_arr, int cmd_len)
{
	if (!ft_strncmp(cmd_arr[0], "pwd", cmd_len))
	{
		printf("%s\n", g_main.current_path);
		return (1);
	}
	else if (!ft_strncmp(cmd_arr[0], "env", cmd_len))
	{
		print_envp();
		return (1);
	}
	else if (!ft_strncmp(cmd_arr[0], "echo", cmd_len))
	{
		shell_echo(cmd_arr);
		return (1);
	}
	else if (!ft_strncmp(cmd_arr[0], "export", cmd_len) \
	&& array2d_y(cmd_arr) == 1)
	{
		add_to_envp(cmd_arr[1]);
		return (1);
	}
	return (0);
}

int	execute_builtins(char **cmd, int cmd_listlen)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd[0]);
	if (cmd_listlen == 1)
	{
		if (!ft_strncmp(cmd[0], "cd", cmd_len))
		{
			changing_dir(cmd);
			return (1);
		}
		else if (!ft_strncmp(cmd[0], "unset", cmd_len)
			&& array2d_y(cmd) == 2)
		{
			remove_envp(cmd[1]);
			return (1);
		}
		else if (!ft_strncmp(cmd[0], "exit", cmd_len) && array2d_y(cmd) == 1)
			return (2);
		else if (!ft_strncmp(cmd[0], "export", cmd_len) && array2d_y(cmd) == 2)
		{
			add_to_envp(cmd[1]);
			return (1);
		}
	}
	return (execute_builtins1(cmd, cmd_len));
}

int	execute(t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		exit_status;

	init_fds(cmd_list);
	temp = cmd_list;
	exit_status = 0;
	while (temp)
	{
		exit_status = execute_builtins(temp->cmds, cmd_list_len(cmd_list));
		if (exit_status <= 1)
			execute_child(temp);
		temp = temp->next;
	}
	wait(NULL);
	return (exit_status);
}

// t_cmd	*init_struct(char *f1, char *f2, char *cmd)
// {
// 	t_cmd	*head = malloc(sizeof(t_cmd));

// 	head->cmds = ft_split(cmd, ' ');
// 	if (!f1)
// 		head->fd_in = 0;
// 	else
// 		head->fd_in = open(f1, O_RDONLY, 0666);
// 	if (!f2)
// 		head->fd_out = 1;
// 	else
// 		head->fd_out = open(f2, O_CREAT | O_RDWR | O_TRUNC, 0666);
// 	head->next = NULL;
// 	head->prev = NULL;
// 	pipe(head->pipe);
// 	// printf("pipe of %s [%d, %d]\n", head->cmd[0], head->pipe[0], head->pipe[1]);
// 	return (head);
// }

// // PROBLEM
// // now ls -l is not running for some reason
// // i speculate it to be a pipe error or a dup2 error

// int main(int ac, char **av, char **envp)
// {
// 	g_main.envp = envp_dup(envp);
// 	// init_struct(1 ,2 ,3);
// 	// 1 = filename of input or NULL for default in
// 	// 2 = filename of output or NULL for default out
// 	// 3 = cmd with spaces separating cmd and flags(not working properly if got spaces in the arguments)
// 	t_cmd *head = init_struct("test.c", NULL, "sort");
// 	t_cmd *mid = init_struct(NULL, NULL, "cat -e");
// 	t_cmd *end = init_struct(NULL, "out", "wc -l");
// 	head->next = mid;
// 	mid->next = end;
// 	mid->prev = head;
// 	end->prev = mid;
// 	// execve("/bin/cat", head->cmd, g_main.envp);
// 	execute_temp(head);
// 	// char *temp = merge_path(ft_strjoin("/", ft_strdup("cat")));
// 	// printf("%s\n", temp);
// 	return (0);
// }