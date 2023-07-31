/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:19:17 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/31 10:48:40 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this function is used by the add_to_envp function to find the '=' char
int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

// prints the envp
void	print_envp(void)
{
	int	i;

	i = 0;
	while (g_main.envp[i])
		printf("%s\n", g_main.envp[i++]);
}

void	print_export(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_main.envp[i])
	{
		printf("declare -x ");
		j = 0;
		while (g_main.envp[i][j])
		{
			printf("%c", g_main.envp[i][j]);
			if (g_main.envp[i][j] == '=')
				printf("\"");
			j++;
		}
		printf("\"\n");
		i++;
	}
}

void	freeing_2darray(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*merge_path(char *c)
{
	int		i;
	char	*r_str;
	char	**paths;
	char	*temp;

	if (!c)
		return (NULL);
	temp = shell_getenv("PATH");
	paths = ft_split(temp, ':');
	free(temp);
	i = -1;
	while (paths[++i])
	{
		r_str = ft_strjoin(paths[i], c);
		if (!r_str)
			continue ;
		if (access(r_str, F_OK | X_OK) == 0)
			break ;
		free(r_str);
		r_str = NULL;
	}
	free(c);
	freeing_2darray(paths);
	if (!r_str)
		return (NULL);
	return (r_str);
}
