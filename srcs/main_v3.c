/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:21:47 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/12 11:44:39 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// idk types yet but we can figure it out on the way
// 0 for nothing yet
// 1 for command
// 2 for flags
// 3 for operators like >> and << , <, >
// 4 here_doc
// 5 for file names
// 6 for pipes

// int	check_operator(char *c)
// {
// 	if (!ft_strncmp(c, ">>", ft_strlen(c))
// 		|| !ft_strncmp(c, "<", ft_strlen(c)) || !ft_strncmp(c, ">", ft_strlen(c)))
// 		return (1);
// 	return (0);
// }

// int	check_here_doc(char *c)
// {
// 	if (!ft_strncmp(c, "<<", ft_strlen(c)))
// 		return (1);
// 	return (0);
// }

// int check_pipe(char *c)
// {
// 	if (!ft_strncmp(c, "|", ft_strlen(c)))
// 		return (1);
// 	return (0);
// }

// int	assign_type(t_command **c)
// {
// 	t_command	*temp_c;
// 	char *temp;
// 	int	i = 0;
// 	int	c_len = c_size(*c);
// 	while (i < c_size)
// 	{
// 		temp_c = c_goto(*c, i);
// 		temp = temp_c->line;
// 		if ()
// 		if (check_operator(temp) == 1)
// 			temp_c->type = 3;
// 		if (check_here_doc(temp) == 1)
// 			temp_c->type = 4;
// 		if (check_pipe(temp) == 1)
// 			temp_c->type = 5;
// 	}
// }

// int	parsing(char **in)
// {
// 	t_command	*new_list = NULL;
// 	t_command	*temp;
// 	int i = -1;
// 	while (in[++i])
// 	{
// 		temp = c_new(in[i], 0);
// 		if (!temp)
// 		{
// 			c_clear(&new_list);
// 			return (-1);
// 		}
// 		c_addback(&new_list, temp);
// 	}
// 	assign_type(&new_list);
// 	return (0);
// }

// for handling "ctrl" + "\" which normally kills the program
// void	signal_handler_ctrl_s(int signum)
// {
// 	return ;
// }

// // for handling "ctrl" + "c"
// void	signal_handler_ctrl_c(int signum)
// {
// 	// sigint(2)
// 	// idk yet this is smt for later
// }

// // for handling "ctrl" + "d"
// void	signal_handler_ctrl_d(int signum)
// {
// 	// idk how to exit without mem leaks through this
// 	exit (0);
// }

//int	sig = 0;

// // for handling "ctrl" + "c"
void	signal_handler_ctrl_c(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	array2d_y(char **a)
{
	int i = 0;
	while (a[i])
		i++;
	return (i);
}

int	command_exe(char *input, char **envp)
{
	char	**temp;
	char	*temp1;

	if (!input || !*input || *input == EOF)
		return (0);
	temp = ft_split(input, ' ');
	if (!temp)
		return (-1);
	if (temp[0] && !(ft_strncmp(temp[0], "exit", ft_strlen(temp[0])))
		&& array2d_y(temp) == 1)
		return (-1);
	temp1 = merge_path(ft_strjoin("/", temp[0]));
	if (temp1)
	{
		printf("Command found at -> %s\n", temp1);
	}
	else
	{
		printf("minishell: %s: command not found\n", temp[0]);
	}
	freeing_2darray(temp);
	return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char	*input;

    printf("\nProgram started\n");
    printf("-------------------------------\n\n");
	signal(SIGINT, signal_handler_ctrl_c);
	int in = 0;
    while (!in)
    {
        input = readline("minishell: ");
		if (!input)
			break ;
		in = command_exe(input, envp);
		if (input)
        	free(input);
    }
    printf("------- *Program ended* -------\n");
    return (0);
}

// int main(void)
// {
// 	printf("%d\n", find_length("    almo"));
// 	printf("%d\n", find_length(" a   almo  "));
// 	printf("%d\n", find_length("almo"));
// 	printf("%d\n", find_length("   cat     "));
// 	// printf("%d\n", find_length(""));
// 	// printf("%d\n", find_length(NULL));
	
// 	printf("%s\n", remove_extra_spaces("   cat     "));
// }