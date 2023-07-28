/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:33:49 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/28 08:41:57 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_error(char *cmd_path, t_cmd *cmd_lst)
{
	t_cmd	*temp;

	temp = cmd_lst;
	ft_putstr_fd("\033[95mminishell\033[0;37m: \033[0;31m", 2);
	ft_putstr_fd(cmd_lst->cmds[0], 2);
	ft_putstr_fd("\033[0;37m: command not found\n", 2);
	free(cmd_path);
	while (temp->prev)
		temp = temp->prev;
	cmd_clear(&cmd_lst);
	freeing_2darray(g_main.envp);
	exit(EXIT_FAILURE);
}

int	exec_action_builtins(char **cmd, int cmd_lst_len)
{
	int	i;

	i = 1;
	if (!(cmd_lst_len >= 1 && cmd_lst_len <= 2))
		return (0);
	if (!ft_strncmp(cmd[0], "cd", 3))
		changing_dir(cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6) && cmd_lst_len == 2)
		remove_envp(cmd[1]);
	else if (!ft_strncmp(cmd[0], "export", 7) && array2d_y(cmd) > 1)
		while (cmd[i])
			add_to_envp(cmd[i++]);
	else if (!ft_strncmp(cmd[0], "exit", 5) && cmd_lst_len == 1)
		return (EXIT_SHELL);
	else
		return (0);
	return (ACTION_BUILTIN);
}

// used to execute display builtins like pwd for path or env for envp
int	exec_display_builtins(char **cmd)
{
	if (!ft_strncmp(cmd[0], "pwd", 4))
		printf("%s\n", g_main.current_path);
	else if (!ft_strncmp(cmd[0], "env", 4))
		print_envp();
	else if (!ft_strncmp(cmd[0], "echo", 5))
		shell_echo(cmd);
	else if (!ft_strncmp(cmd[0], "export", 7) && !cmd[1])
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
void	execute_child(t_cmd *cmd_list)
{
	pid_t	pid;
	char	*temp;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (cmd_list->fd_in != 0)
			dup2(cmd_list->fd_in, STDIN_FILENO);
		if (cmd_list->fd_out != 1)
			dup2(cmd_list->fd_out, STDOUT_FILENO);
		if (cmd_list->next != NULL)
			close(cmd_list->next->pipe[0]);
		if (exec_display_builtins(cmd_list->cmds) == DISPLAY_BUILTIN)
			exit(EXIT_SUCCESS);
		execve(cmd_list->cmds[0], cmd_list->cmds, g_main.envp);
		temp = merge_path(ft_strjoin("/", cmd_list->cmds[0]));
		execve(temp, cmd_list->cmds, g_main.envp);
		cmd_error(temp, cmd_list);
	}
	else
		if (cmd_list->next != NULL)
			close(cmd_list->next->pipe[1]);
}

void	cleaning_unused_fd(t_cmd *cmd_lst, int *default_std)
{
	t_cmd	*temp;

	if (!cmd_lst)
		return ;
	temp = cmd_lst;
	while (temp)
	{
		if (temp->pipe_stat == 1)
			close(temp->pipe[0]);
		temp = temp->next;
	}
	dup2(default_std[0], STDIN_FILENO);
	dup2(default_std[1], STDOUT_FILENO);
	close(default_std[0]);
	close(default_std[1]);
}

int	execute(t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		exit_status;
	int		cmd_list_len;
	int		default_std[2];
	int		child_count;

	init_fds(cmd_list);
	temp = cmd_list;
	exit_status = 0;
	cmd_list_len = get_cmd_list_len(cmd_list);
	default_std[0] = dup(STDIN_FILENO);
	default_std[1] = dup(STDOUT_FILENO);
	child_count = 0;
	// ft_putnbr_fd(d_in, 2);
	// ft_putchar_fd('\n', 2);
	// ft_putnbr_fd(d_out, 2);
	// ft_putchar_fd('\n', 2);
	while (temp)
	{
		exit_status = exec_action_builtins(temp->cmds, cmd_list_len);
		if (exit_status == EXIT_SHELL || exit_status == ACTION_BUILTIN)
			break ;
		if (exit_status == 0 || (exit_status == DISPLAY_BUILTIN && cmd_list_len > 1))
			execute_child(temp);
		child_count++;
		temp = temp->next;
	}
	while (child_count--)
		wait(NULL);
	cleaning_unused_fd(cmd_list, default_std);
	return (exit_status);
}

// display
// 	pwd
// 	env
// 	echo [string]
// 	export
// action
// 	cd [path]
// 	unset [var]
// 	exit
// 	export [var]

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