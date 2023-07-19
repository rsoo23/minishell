/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:13:10 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/19 13:42:15 by rsoo             ###   ########.fr       */
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
	if (array2d_y(a) == 1)
		return ((void)printf("\n"));
	if (array2d_y(a) == 2)
		return ((void)printf("%s\n", a[1]));
	if (array2d_y(a) == 3 && !ft_strncmp(a[1], "-n", 3))
		printf("%s", a[2]);
}
