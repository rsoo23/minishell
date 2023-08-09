/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:52:25 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/09 20:58:01 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_main	g_main;

// the init function first duplicates the envp and saves it to a 2d char array
// then we just get the pointer that points to the PWD and the HOME 
// variables and save it to char pointers for easier use for later
// (shell_getenv is equivalent to getenv but for our global struct)
void	main_init(char **envp)
{
	char	*pwd;

	g_main.envp = envp_dup(envp);
	pwd = shell_getenv("PWD");
	g_main.current_path = malloc(PATH_MAX);
	ft_strlcpy(g_main.current_path, pwd, ft_strlen(pwd) + 1);
	g_main.user_path = shell_getenv("HOME");
	free(pwd);
	pwd = ft_strjoin("SHELL=", g_main.current_path);
	add_to_envp(pwd);
	free(pwd);
	g_main.print_flag = 1;
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
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	if (g_main.print_flag)
		rl_redisplay();
}

void	cmd_clear(t_cmd **cmd_list)
{
	t_cmd	*temp;

	if (!cmd_list)
		return ;
	while (*cmd_list)
	{
		temp = *cmd_list;
		*cmd_list = (*cmd_list)->next;
		freeing_2darray(temp->cmds);
		if (temp->infile_name)
			free(temp->infile_name);
		free(temp);
	}
	cmd_list = NULL;
}

void	initialize(char	**envp)
{
	print_welcome();
	main_init(envp);
	tcgetattr(0, &g_main.origi_attri);
	tcgetattr(0, &g_main.new_attri);
	g_main.new_attri.c_lflag &= ~ECHOCTL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	tcsetattr(0, TCSANOW, &g_main.new_attri);
}

// the main where we initialize the g_main variable and print the welcome msg
// the while loop inside is checking if the return value of the parsing func
// to see if the user inputed "exit" and will stop the loop when the user does
// so. finishing up is a func that will return 0 for norminette sake and also
// clean up the envp variable and also print out the end msg
int	main(int ac, char **av, char **envp)
{
	int		exit_status;

	(void)ac;
	(void)av;
	exit_status = 0;
	initialize(envp);
	while (exit_status != EXIT_SHELL)
	{
		if (!get_input())
			break ;
		if (!intepret_input(&g_main.tokens_info, g_main.user_input))
		{
			delete_token_list(&g_main.tokens_info.token_list);
			continue ;
		}
		parse(&g_main.tokens_info.token_list, &g_main.cmd_list);
		exit_status = execute(g_main.cmd_list);
		cmd_clear(&g_main.cmd_list);
	}
	return (end_minishell());
}
