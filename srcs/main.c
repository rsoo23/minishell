/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:52:25 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/19 00:33:16 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	g_main;

// frees the envp(thats the only one we malloced)
// then it prints out the end msg
int	finishing_up(void)
{
	freeing_2darray(g_main.envp);
	printf("\n\033[96m╔═════════════════════════════════════");
	printf("═══════════════════════════════════════════╗\n");
	printf("║                              \033[0;37m*  prog");
	printf("ram ended  *                               \033[96m║\n");
	printf("╚═══════════════════════════════════════════");
	printf("═════════════════════════════════════╝\033[0;37m\n\n");
	return (0);
}

// prints the 2nd part of the welcome msg
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

// prints the first part of the welcome msg
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

// shell_strjoin joins 3 strings together and based on the num variable
// it will free the 2nd string (cause funny multiple function in one line)
char	*shell_strjoin(char const *s1, char *s2, char const *s3, int num)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	if (!s1 || !s2 | !s3)
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

// this func will finc the path of the executable from the PATH in envp
// if its not found it will try the current directory
// if it fails then it will print an error message
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

// this func returns a pointer to the variable from the envp
char	*shell_getenv(char *s)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (g_main.envp[i])
	{
		j = 0;
		while (s[j] == g_main.envp[i][j] && j < len)
			j++;
		if (!s[j])
			return (g_main.envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

// this func compiles the current path and the "minishell" string to a nice
// string all together, it will check if the current path is the HOME path
// from the envp if it is it will compile it to "minishell: ~$"
char	*name_finder(char *s)
{
	char	*r_str;
	char	*temp;
	int		i;
	int		s_index;

	i = 0;
	temp = NULL;
	if (!ft_strncmp(s, shell_getenv("HOME"), ft_strlen(s) + 1))
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

// this function will attemp to cd into a folder
// it will print out an error msg if it fails
int	changing_dir(char **arr)
{
	if (!arr[1])
		chdir(shell_getenv("HOME"));
	else if (chdir(arr[1]) == -1)
	{
		printf("\033[95mminishell\033[0;37m: cd: \033[0;31m%s", arr[1]);
		printf("\033[0;37m: No such file or directory\n");
	}
	getcwd(g_main.current_path, PATH_MAX);
	return (0);
}

// this function gets the y axis of a 2d char array
int	array2d_y(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

// this func creates a 2d array and copies the envp
// then it strdup the user input and saves it to the end of the newly created 
// array, then it frees the old 2d pointer
char	**array_append(char **a, char *line)
{
	char	**r_a;
	int		i;

	if (!line)
		return (a);
	if (!a)
	{
		r_a = malloc(2 * sizeof(char *));
		r_a[0] = ft_strdup(line);
		r_a[1] = NULL;
		return (r_a);
	}
	i = -1;
	r_a = malloc((array2d_y(a) + 2) * sizeof(char *));
	if (!r_a)
		return (NULL);
	while (a[++i])
		r_a[i] = a[i];
	r_a[i++] = ft_strdup(line);
	r_a[i] = NULL;
	free(a);
	return (r_a);
}

// this function is used by the add_to_envp function to find the '=' char
int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

// it first tries to find the '=' in the string given
// if its not found then it will just end there
// else it will loop through the envp and will top if the envp[i] is NULL 
// or if the current variable name on the line of envp[i] is the same with 's'
// then if it does find the same variable name then it will free that variable
// and strdup the user input and replace the line in the envp
// else if it does not find a same name then it will call de array_appen func
void	add_to_envp(char *s)
{
	int	i;
	int	pos;

	if (!s)
		return (print_envp());
	i = 0;
	pos = find_char(s, '=');
	if (pos == (int)ft_strlen(s))
		return ;
	while (g_main.envp[i] && !!ft_strncmp(s, g_main.envp[i], pos))
		i++;
	if (g_main.envp[i])
	{
		free(g_main.envp[i]);
		g_main.envp[i] = ft_strdup(s);
		return ;
	}
	g_main.envp = array_append(g_main.envp, s);
}

// this function creates a new 2d array to transfer all the pointers over
// from the current envp, it just saves the pointers to it and removes the one
// given by the user, then when it finishes it NULL terminates the array
// then it returns it
char	**remove_envp(char *s)
{
	int		i;
	int		len;
	char	**r_a;

	if (!s)
		return (NULL);
	r_a = malloc(array2d_y(g_main.envp) * sizeof(char *));
	if (!r_a)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	while (g_main.envp[++i] && !!ft_strncmp(s, g_main.envp[i], len))
		r_a[i] = g_main.envp[i];
	if (g_main.envp[i])
	{
		free(g_main.envp[i]);
		while (g_main.envp[++i])
			r_a[i - 1] = g_main.envp[i];
		i--;
	}
	r_a[i] = NULL;
	free(g_main.envp);
	return (r_a);
}

// this function checks if the current envp has the same string 's'
// if it does then it sends it to the remove_envp function
// else it does nothing
void	unset_envp(char *s)
{
	int	i;
	int	len;

	if (!s)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (g_main.envp[i] && !!ft_strncmp(s, g_main.envp[i], len))
		i++;
	if (g_main.envp[i])
		g_main.envp = remove_envp(s);
}

// this is replica of the echo command but we need to tweek it for later when
// we finish the $sign so we can call the envp variable
void	shell_echo(char **a)
{
	if (array2d_y(a) == 1)
		return ((void)printf("\n"));
	if (array2d_y(a) == 2)
		return ((void)printf("%s\n", a[1]));
	if (array2d_y(a) == 3 && !ft_strncmp(a[1], "-n", 3))
		printf("%s", a[2]);
}

// temp parser
// it first splits the input by space then checks for the first 
// element in the array to see if its a built in function
// else it tries to run it with execve with the create_child function
int	parsing(char *s, char **envp)
{
	int		len;
	char	**arr;

	if (!s)
		return (0);
	arr = ft_split(s, ' ');
	len = ft_strlen(arr[0]) + 1;
	g_main.arr = arr;
	if (!arr)
		return (0);
	if (arr[0] && !ft_strncmp(arr[0], "cd", len))
		changing_dir(arr);
	else if (arr[0] && !ft_strncmp(arr[0], "pwd", len))
		printf("%s\n", g_main.current_path);
	else if (arr[0] && !ft_strncmp(arr[0], "exit", len) && array2d_y(arr) == 1)
		return (1);
	else if (arr[0] && !ft_strncmp(arr[0], "export", len))
		add_to_envp(arr[1]);
	else if (arr[0] && !ft_strncmp(arr[0], "unset", len)
		&& array2d_y(arr) == 2)
		g_main.envp = remove_envp(arr[1]);
	else if (arr[0] && !ft_strncmp(arr[0], "env", len))
		print_envp();
	else if (arr[0] && !ft_strncmp(arr[0], "echo", len))
		shell_echo(arr);
	else if (arr[0])
		create_child(envp);
	freeing_2darray(g_main.arr);
	g_main.arr = NULL;
	return (0);
}

// this function duplicates the envp
// if it fails then it will return NULL but idk what we should do in
// that case
char	**envp_dup(char **envp)
{
	char	**n_envp;
	int		i;

	i = -1;
	n_envp = malloc((array2d_y(envp) + 1) * sizeof(char *));
	if (!n_envp)
		return (NULL);
	while (envp[++i])
	{
		n_envp[i] = ft_strdup(envp[i]);
		if (!n_envp[i])
		{
			freeing_2darray(n_envp);
			return (NULL);
		}
	}
	n_envp[i] = NULL;
	return (n_envp);
}

// de init function first duplicates the envp and saves it to a 2d char array
// den we just get the pointer that points to the PWD and the HOME 
// variables and save it to char pointers for easier use for later
// (shell_getenv is equivalent to getenv but for our global struct)
void	main_init(char **envp)
{
	g_main.envp = envp_dup(envp);
	g_main.current_path = shell_getenv("PWD");
	g_main.user_path = shell_getenv("HOME");
}

// this is the signal handler where when a signal is pass through and check if 
// the signal is equal to SIGINT and print a new line
// then it tells the readline function that it is on a newline
// the it replaces that line cause if the user inputed some characters
// the newline will carry over those characters aswell so we have to replace it
// rl_display re display the message it was given to print before
void	sig_handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// the main where we initialize the g_main variable and print the welcome msg
// the while loop inside is checking if the return value of the parsing func
// to see if the user inputed "exit" and will stop the loop when the user does
// so. finishing up is a func that will return 0 for norminette sake and also
// clean up the envp variable and also print out the end msg
int	main(int ac, char **av, char **envp)
{
	char	*temp;
	int		in;

	(void)ac;
	(void)av;
	main_init(envp);
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
		// added:
		tokenize(&g_main.tokens_info, g_main.user_input);
		parsing(&g_main.tokens_info.token_list, &g_main.cmd_list);
		delete_all_tokens(&g_main.tokens_info.token_list);
		//
		in = parsing(g_main.user_input, envp);
		free(g_main.user_input);
	}
	return (finishing_up());
}

// when exporting we need to 
