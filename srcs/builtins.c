/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:13:10 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/10 09:02:50 by lewlee           ###   ########.fr       */
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
		printf("minishell\033[0;37m: cd: \033[0;31m%s", arr[1]);
		printf("\033[0;37m: No such file or directory\n");
	}
	else
	{
		temp = ft_strjoin("OLDPWD=", g_main.current_path);
		add_to_envp(temp);
		free(temp);
	}
	getcwd(g_main.current_path, PATH_MAX);
	temp = ft_strjoin("PWD=", g_main.current_path);
	add_to_envp(temp);
	free(temp);
	return (0);
}

// this is replica of the echo command but we need to tweek it for later when
// we finish the $sign so we can call the envp variable
void	shell_echo(char **a)
{
	int	i;
	int	nl_flag;

	if (array2d_y(a) == 1)
		return ((void)printf("\n"));
	nl_flag = 0;
	i = 1;
	while (a[i] && !ft_strncmp(a[i], "-n", ft_strlen(a[i])))
	{
		if (!ft_strncmp(a[i], "-n", ft_strlen(a[i])))
		{
			nl_flag = 1;
			i++;
			continue ;
		}
	}
	while (a[i])
	{
		printf("%s", a[i++]);
		if (a[i])
			printf(" ");
	}
	if (nl_flag != 1)
		printf("\n");
}
