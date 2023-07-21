/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:52:25 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/21 11:00:57 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	g_main;

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

// this is for later when we have an executor ready
// set signal as default first
// then only create child
// then at wait pid area you set the signal to sig_handler_child
void	sig_handler_child(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
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
	print_welcome();
	while (!in)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		temp = name_finder(g_main.current_path);
		g_main.user_input = readline(temp);
		free(temp);
		if (!g_main.user_input)
			break ;
		add_history(g_main.user_input);
		tokenize(&g_main.tokens_info, g_main.user_input);
		parse(&g_main.tokens_info.token_list, &g_main.cmd_list);
		delete_all_tokens(&g_main.tokens_info.token_list);
		execute(g_main.cmd_list);
		free(g_main.user_input);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	return (finishing_up());
}
