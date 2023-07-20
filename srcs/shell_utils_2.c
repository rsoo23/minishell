/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:19:17 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/19 10:37:40 by lewlee           ###   ########.fr       */
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

void	freeing_2darray(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*merge_path(char *c)
{
	int		i;
	char	*r_str;
	char	**paths;

	if (!c)
		return (NULL);
	paths = ft_split(shell_getenv("PATH"), ':');
	i = -1;
	if (!paths || !*paths)
		return (NULL);
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
