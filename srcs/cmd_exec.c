/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:11:29 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/19 10:37:20 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this func will finc the path of the executable from the PATH in envp
// if its not found it will try the current directory
// if it fails then it will print an error message
static void	child_process(t_main *main, char **envp)
{
	char	*temp;

	temp = merge_path(ft_strjoin("/", main->arr[0]));
	if (!temp)
		temp = shell_strjoin(main->current_path, "/", main->arr[0], 0);
	execve(temp, main->arr, envp);
	free(temp);
	printf("\033[95mminishell\033[0;37m: \033[0;31m%s", main->arr[0]);
	printf("\033[0;37m: command not found\n");
	exit(1);
}

// this func creates a child (v basic)
int	create_child(char **envp)
{
	pid_t	pid;
	t_main	main;

	main = g_main;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
		child_process(&main, envp);
	else
		waitpid(pid, NULL, 0);
	return (0);
}
