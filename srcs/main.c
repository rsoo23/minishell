/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:52:25 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/19 10:42:16 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	g_main;

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
		remove_envp(arr[1]);
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
