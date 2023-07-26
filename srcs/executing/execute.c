/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:49 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/26 12:43:05 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_temp(void)
{
	printf("ERROR cmd not found\n");
	exit(EXIT_FAILURE);
}

void	execute(t_cmd *inst)
{
	pid_t	pid;
	char	*temp;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (inst->fd_out != 1)
			dup2(inst->fd_out, STDOUT_FILENO);
		if (inst->fd_in != 0)
			dup2(inst->fd_in, STDIN_FILENO);
		if (inst->next != NULL)
			close(inst->next->pipe[0]);
		temp = merge_path(ft_strjoin("/", inst->cmd[0]));
		if (!temp)
			return ;
		execve(temp, inst->cmd, g_main.envp);
		error_temp();
	}
	else
		if (inst->next != NULL)
			close(inst->next->pipe[1]);
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
	int	cmdl;

	cmdl = ft_strlen(cmd[0]);
	if (cmd_listlen == 1)
	{
		if (!ft_strncmp(cmd[0], "cd", cmdl))
		{
			changing_dir(cmd);
			return (1);
		}
		else if (!ft_strncmp(cmd[0], "unset", cmdl)
			&& array2d_y(cmd) == 2)
		{
			remove_envp(cmd[1]);
			return (1);
		}
		else if (!ft_strncmp(cmd[0], "exit", cmdl) && array2d_y(cmd) == 1)
			exit(0);
		else if (!ft_strncmp(cmd[0], "export", cmdl) && array2d_y(cmd) == 2)
		{
			add_to_envp(cmd[1]);
			return (1);
		}
	}
	return (execute_builtins1(cmd, cmd_listlen));
}

void	execute_temp(t_cmd *inst)
{
	t_cmd	*temp;
	int		d_in;
	int		d_out;

	d_in = dup(STDIN_FILENO);
	d_out = dup(STDOUT_FILENO);
	init_fds(inst);
	temp = inst;
	while (temp)
	{
		if (execute_builtins(temp->cmd, cmd_list_len(inst)) != 1)
			execute(temp);
		temp = temp->next;
	}
	wait(NULL);
}

// t_cmd	*init_struct(char *f1, char *f2, char *cmd)
// {
// 	t_cmd	*head = malloc(sizeof(t_cmd));

// 	head->cmd = ft_split(cmd, ' ');
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