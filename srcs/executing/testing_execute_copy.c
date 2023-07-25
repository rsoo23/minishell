/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_execute copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:49 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/25 13:30:15 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_main g_main;

int	array2d_y(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

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
		if (inst->next != NULL)
			close(inst->next->pipe[0]);
		temp = merge_path(ft_strjoin("/", inst->cmd[0]));
		if (!temp)
			return ;
		execve(temp, inst->cmd, g_main.envp);
		error_temp();
	}
	else
	{
		if (inst->fd_in == 0)
			wait(NULL);
		if (inst->next != NULL)
			close(inst->next->pipe[1]);
	}
}

void	init_fds(t_cmd *lst)
{
	t_cmd	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->fd_in == 0 && temp->prev != NULL)
			temp->fd_in = temp->prev->pipe[0];
		if (temp->fd_out == 1 && temp->next != NULL)
			temp->fd_out = temp->next->pipe[1];
		temp = temp->next;
	}
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
		if (temp->fd_out != 1)
			dup2(temp->fd_out, STDOUT_FILENO);
		else
			dup2(d_out, STDOUT_FILENO);
		if (temp->fd_in != 0)
			dup2(temp->fd_in, STDIN_FILENO);
		else
			dup2(d_in, STDIN_FILENO);
		execute(temp);
		temp = temp->next;
	}
}

t_cmd *init_struct(char *f1, char *f2, char *cmd)
{
	t_cmd *head = malloc(sizeof(t_cmd));
	head->cmd = ft_split(cmd, ' ');
	if (!f1)
		head->fd_in = 0;
	else
		head->fd_in = open(f1, O_RDONLY, 0666);
	if (!f2)
		head->fd_out = 1;
	else
		head->fd_out = open(f2, O_CREAT | O_RDWR | O_TRUNC, 0666);
	head->next = NULL;
	head->prev = NULL;
	pipe(head->pipe);
	return (head);
}

// PROBLEM
// now ls -l is not running for some reason
// i speculate it to be a pipe error or a dup2 error

int main(int ac, char **av, char **envp)
{
	g_main.envp = envp_dup(envp);
	t_cmd *head = init_struct("test.c", NULL, "sort");
	t_cmd *mid = init_struct("out", "lmao", "ls -l");
	t_cmd *end = init_struct(NULL, "out", "cat");
	head->next = mid;
	mid->next = end;
	mid->prev = head;
	end->prev = mid;
	// execve("/bin/cat", head->cmd, g_main.envp);
	execute_temp(head);
	// char *temp = merge_path(ft_strjoin("/", ft_strdup("cat")));
	// printf("%s\n", temp);
	return (0);
}