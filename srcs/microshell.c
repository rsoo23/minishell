/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:52:25 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/15 20:27:49 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	g_main;

int	finishing_up(void)
{
	free(g_main.user_path);
	free(g_main.current_path);
	printf("\n\033[96m══════════════════════════════  \033[0;37m* program");
	printf(" ended *  \033[96m═══════════════════════════════\n\n\033[0;37m");
	return (0);
}

void	print_welcome1(void)
{
	printf("║      \033[0;37m ████╗░████║██║████╗░██║██║");
	printf("██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░       \033[96m║\n");
	printf("║      \033[0;37m ██╔████╔██║██║██╔██╗██║██║");
	printf("╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░       \033[96m║\n");
	printf("║      \033[0;37m ██║╚██╔╝██║██║██║╚████║██║");
	printf("░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░       \033[96m║\n");
	printf("║      \033[0;37m ██║░╚═╝░██║██║██║░╚███║██║");
	printf("██████╔╝██║░░██║███████╗███████╗███████╗       \033[96m║\n");
	printf("║      \033[0;37m ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝");
	printf("╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝       \033[96m║\n");
	printf("║                                           ");
	printf("                                     ║\n");
	printf("╚═══════════════════════════════════════════");
	printf("═════════════════════════════════════╝\n\n");
}

void	print_welcome(void)
{
	printf("\033[96m╔═════════════════════════════════════");
	printf("═══════════════════════════════════════════╗\n");
	printf("║                                             ");
	printf("                                   ║\n");
	printf("║                          \033[0;37mA project");
	printf(" brought to you by                           \033[96m║\n");
	printf("║                              \033[0;37mRsoo ");
	printf("   &&    Lewlee                              \033[96m║\n");
	printf("║                                             ");
	printf("                                   ║\n");
	printf("║      \033[0;37m ███╗░░░███╗██╗███╗░░██╗██╗");
	printf("░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░       \033[96m║\n");
	print_welcome1();
}

void	child_process(t_main *main, char **envp)
{
	char	*temp;

	temp = merge_path(ft_strjoin("/", main->arr[0]));
	execve(temp, main->arr, envp);
	free(temp);
	printf("\033[95mminishell\033[0;37m: \033[0;31m%s", main->arr[0]);
	printf("\033[0;37m: command not found\n");
	exit(1);
}

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

char	*name_finder(char *s)
{
	char	*r_str;
	int		i;
	int		s_index;

	i = 0;
	r_str = NULL;
	while (s[i])
		if (s[i++] == '/')
			s_index = i;
	if (i != 0)
	{
		r_str = ft_strndup(s + s_index, i - s_index);
		if (!r_str)
			return (NULL);
	}
	return (r_str);
}

int	changing_dir(char **arr)
{
	if (!arr[1])
		chdir(g_main.user_path);
	else if (chdir(arr[1]) == -1)
	{
		printf("\033[95mminishell\033[0;37m: cd: \033[0;31m%s", arr[1]);
		printf("\033[0;37m: No such file or directory\n");
	}
	getcwd(g_main.current_path, PATH_MAX);
	return (0);
}

int	array2d_y(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

int	parsing(char *s, char **envp)
{
	char	**arr;

	if (!s)
		return (0);
	arr = ft_split(s, ' ');
	g_main.arr = arr;
	if (!arr)
		return (0);
	if (arr[0] && !ft_strncmp(arr[0], "cd", ft_strlen(arr[0]) + 1))
		changing_dir(arr);
	else if (arr[0] && !ft_strncmp(arr[0], "pwd", ft_strlen(arr[0]) + 1))
		printf("%s\n", g_main.current_path);
	else if (arr[0] && !ft_strncmp(arr[0], "exit",
			ft_strlen(arr[0]) + 1) && array2d_y(arr) == 1)
		return (1);
	else if (arr[0])
		create_child(envp);
	freeing_2darray(g_main.arr);
	g_main.arr = NULL;
	return (0);
}

t_main	main_init(void)
{
	t_main	main;

	main.current_path = malloc(PATH_MAX * sizeof(char));
	getcwd(main.current_path, PATH_MAX);
	main.user_path = ft_strjoin("/Users/", getenv("USER"));
	return (main);
}

void	sig_handler(int signum)
{
	char	*temp;

	temp = name_finder(g_main.current_path);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\033[95mminishell\033[0;37m: %s$", temp);
	rl_redisplay();
	free(temp);
	if (signum == SIGQUIT)
		return ;
}

int	main(int ac, char **av, char **envp)
{
	char	*temp;
	int		in;

	(void)ac;
	(void)av;
	g_main = main_init();
	in = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	print_welcome();
	while (!in)
	{
		temp = name_finder(g_main.current_path);
		printf("\033[95mminishell\033[0;37m: %s$", temp);
		free(temp);
		g_main.user_input = readline(" ");
		if (!g_main.user_input)
			break ;
		in = parsing(g_main.user_input, envp);
		free(g_main.user_input);
	}
	return (finishing_up());
}
