/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:52:25 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/16 17:31:18 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	g_main;

int	finishing_up(void)
{
	free(g_main.user_path);
	free(g_main.current_path);
	printf("\n\033[96m╔═════════════════════════════════════");
	printf("═══════════════════════════════════════════╗\n");
	printf("║                              \033[0;37m*  prog");
	printf("ram ended  *                               \033[96m║\n");
	printf("╚═══════════════════════════════════════════");
	printf("═════════════════════════════════════╝\033[0;37m\n\n");
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

char	*shell_strjoin(char const *s1, char *s2, char const *s3, int num)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	string = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!string)
		return (NULL);
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	i = 0;
	while (s3[i])
		string[j++] = s3[i++];
	string[j] = '\0';
	if (num == 1)
		free(s2);
	return (string);
}

void	child_process(t_main *main, char **envp)
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
	char	*temp;
	int		i;
	int		s_index;

	i = 0;
	temp = NULL;
	if (!ft_strncmp(s, g_main.user_path, ft_strlen(s) + 1))
	{
		r_str = shell_strjoin("\033[95mminishell\033[0;37m: ", \
		ft_strdup("~"), "$ ", 1);
		return (r_str);
	}
	while (s[i])
		if (s[i++] == '/')
			s_index = i;
	if (i != 0)
	{
		temp = ft_strndup(s + s_index, i - s_index);
		if (!temp)
			return (NULL);
	}
	r_str = shell_strjoin("\033[95mminishell\033[0;37m: ", temp, "$ ", 1);
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
	if (signum == SIGINT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
		g_main.user_input = readline(temp);
		free(temp);
		if (!g_main.user_input)
			break ;
		add_history(g_main.user_input);
		in = parsing(g_main.user_input, envp);
		free(g_main.user_input);
	}
	return (finishing_up());
}
