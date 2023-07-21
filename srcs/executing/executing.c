/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:07:03 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/20 10:07:03 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// temp parser
// it first splits the input by space then checks for the first 
// element in the array to see if its a built in function
// else it tries to run it with execve with the create_child function
void	execute_builtins(char **cmd_arr)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd_arr[0]);
	if (!ft_strncmp(cmd_arr[0], "cd", cmd_len))
		changing_dir(cmd_arr);
	else if (!ft_strncmp(cmd_arr[0], "export", cmd_len))
		add_to_envp(cmd_arr[1]);
	else if (!ft_strncmp(cmd_arr[0], "unset", cmd_len)
		&& array2d_y(arr) == 2)
		remove_envp(cmd_arr[1]);
	else if (!ft_strncmp(cmd_arr[0], "exit", cmd_len) && array2d_y(arr) == 1)
		exit(0);
	else if (!ft_strncmp(cmd_arr[0], "pwd", cmd_len))
		printf("%s\n", g_main.current_path);
	else if (!ft_strncmp(cmd_arr[0], "env", cmd_len))
		print_envp();
	else if (!ft_strncmp(cmd_arr[0], "echo", cmd_len))
		shell_echo(arr);
}

// this func will finc the path of the executable from the PATH in envp
// if its not found it will try the current directory
// if it fails then it will print an error message
void	execute_cmd(char **cmd_arr)
{
	char	*temp;

	temp = merge_path(ft_strjoin("/", cmd_arr[0]));
	if (!temp)
		temp = shell_strjoin(g_main.current_path, "/", cmd_arr[0], 0);
	execve(temp, cmd_arr, g_main.envp);
	free(temp);
	printf("\033[95mminishell\033[0;37m: \033[0;31m%s", cmd_arr[0]);
	printf("\033[0;37m: command not found\n");
	exit(1);
}

void	child_process(t_cmd cmd, int i)
{
	if (i == 0)
		infile_to_pipe(&cmd);
	else if (i + 1 == g_main.num_of_cmds)
		pipe_to_outfile(&cmd);
	else
		pipe_to_pipe(&cmd);
	execute_builtin(cmd.cmds);
	execute_cmd(cmd.cmds);
}

void	execute(t_cmd *cmd_list)
{
	pid_t	pid;
	int		child_index;

	child_index = 0;
	while (cmd_list)
	{
		if (cmd_list->cmds)
		{
			pid = fork();
			if (pid < 0)
				return ;
			if (pid == 0)
				child_process(*cmd_list, child_index++);
		}
		cmd_list = cmd_list->next;
	}
}
