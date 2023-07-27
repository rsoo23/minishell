/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:13:10 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/27 10:13:24 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this function will attemp to cd into a folder
// it will print out an error msg if it fails
int	changing_dir(char **arr)
{
	char	*temp;

	if (!arr[1])
		chdir(shell_getenv("HOME"));
	else if (chdir(arr[1]) == -1)
	{
		printf("\033[95mminishell\033[0;37m: cd: \033[0;31m%s", arr[1]);
		printf("\033[0;37m: No such file or directory\n");
	}
	else
	{
		temp = ft_strjoin("OLDPWD=", g_main.current_path);
		add_to_envp(temp);
		free(temp);
	}
	getcwd(g_main.current_path, PATH_MAX);
	return (0);
}

// this is replica of the echo command but we need to tweek it for later when
// we finish the $sign so we can call the envp variable
void	shell_echo(char **a)
{
	int	i;

	if (array2d_y(a) == 1)
		return ((void)printf("\n"));
	else if (!ft_strncmp(a[1], "-n", ft_strlen(a[1])))
	{
		i = 2;
		while (a[i])
		{
			printf("%s", a[i]);
			if (a[++i])
				printf(" ");
		}
	}
	else
	{
		i = 1;
		while (a[i])
		{
			printf("%s", a[i]);
			if (a[++i])
				printf(" ");
		}
		printf("\n");
	}
}
