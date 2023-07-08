/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:21:47 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/09 00:25:39 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int ft_strlen(const char *s)
// {
//     int i = 0;
//     while (s[i])
//         i++;
//     return (i);
// }

// int ft_strncmp(const char *s1, const char *s2, unsigned long nb)
// {
//     int i;
    
//     i = 0;
//     while (s1[i] == s2[i] && i < nb && s1[i] && s2[i])
//     {
//         if (s1[i + 1] == '\0' && s2[i + 1] != '\0')
//             return (-1);
//         if (s1[i + 1] != '\0' && s2[i + 1] == '\0')
//             return (1);
//         i++;
//     }
//     return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

static int	find_length(char *line)
{
	int		i;
	int		amount;
	char	*ws;

	i = 0;
	amount = 0;
	ws = " \n\t\v\f\r";
	if (!line || !*line)
		return (0);
	while (line[i])
	{
		if (!ft_strchr(ws, line[i]))
			amount++;
		else if (ft_strchr(ws, line[i]) && !ft_strchr(ws, line[i - 1]))
			amount++;
		i++;
	}
	if (ft_strchr(ws, line[i - 1]))
		amount--;
	return (amount);
}

char    *remove_extra_spaces(char *line)
{
    int		i;
	int		j;
	char	*r_str;
	char	*temp;

	i = 0;
	j = 0;
	temp = " \n\t\v\f\r";
	if (!line || !*line)
		return (NULL);
	r_str = malloc((find_length(line) + 1) * sizeof(char));
	if (!r_str)
		return (NULL);
	while (line[i])
	{
		if (!ft_strchr(temp, line[i]))
			r_str[j++] = line[i];
		else if (!ft_strchr(temp, line[i]) && ft_strchr(temp, line[i - 1]))
			r_str[j++] = line[i];
		i++;
	}
	r_str[j] = '\0';
	return (r_str);
}

// int	check_redirects(char *line)
// {
// 	int	i;
// 	int	amount;

// 	i = 0;
// 	amount = 0;
// 	while (line[i])
// 	{
// 		if (line[i])
// 	}
// }

static int	command_exe(char *input, char **envp)
{
	char	**temp;
	char	*temp1;
	
	temp = ft_split(input, ' ');
	if (!temp)
		return (-1);
	temp1 = merge_path(ft_strjoin("/", temp[0]), envp);
	if (temp1)
	{
		printf("Command found at -> %s\n", temp1);
	}
	else
		printf("minishell: %s: command not found\n", temp[0]);
	freeing_2darray(temp);
	return (-1);
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    (void)envp;
    char	*input;

    printf("\nProgram started\n");
    printf("--------------------------------\n\n");
    input = readline("minishell: ");
    while (ft_strncmp(input, "exit", ft_strlen(input)) != 0 &&
        ft_strncmp(input, "stop", ft_strlen(input)) != 0)
    {
		command_exe(input, envp);
        free(input);
        input = readline("minishell: ");
    }
    printf("minishell: *Program ended*\n");
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