/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:35:37 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/04 16:49:39 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freeing_2darray(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char    **getting_paths(char **envp)
{
	int	i = -1;
	while (envp[++i])
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i], ':'));
}

char    *merge_path(char *c, char **envp)
{
    int i = 0;
    char *r_str;
	char **paths = getting_paths(envp);
	if (!paths || !*paths)
		return (NULL);
    while (paths[i])
    {
        r_str = ft_strjoin(paths[i], c);
        if (!r_str)
            continue ;
        if (access(r_str, F_OK | X_OK) == 0)
            break ;
        free(r_str);
        r_str = NULL;
        i++;
    }
	free(c);
	freeing_2darray(paths);
    if (r_str == NULL)
        return (NULL);
    return (r_str);
}
