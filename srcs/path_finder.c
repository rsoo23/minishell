/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:35:37 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/10 11:31:00 by lewlee           ###   ########.fr       */
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

// finds the command path but not sure we need it or not for later as we could use functions that do the command like cd/pwd
char    *merge_path(char *c)
{
    int i;
    char *r_str;
	char **paths;

	if (!c)
		return (NULL);
	paths = ft_split(getenv("PATH"), ':');
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
    if (r_str == NULL)
        return (NULL);
    return (r_str);
}
