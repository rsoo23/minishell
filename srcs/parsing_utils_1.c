/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:49:08 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/17 11:49:08 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	array2d_y(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

char	**append_cmds(char **cmds, char *str)
{
    char	**temp_cmds;
    int		i;

    if (!str)
        return (cmds);
    if (!cmds)
    {
        temp_cmds = malloc(2 * sizeof(char *));
        temp_cmds[0] = ft_strdup(str);
        temp_cmds[1] = NULL;
        return (temp_cmds);
    }
    i = -1;
    temp_cmds = malloc((array2d_y(cmds) + 2) * sizeof(char *));
    if (!temp_cmds)
        return (NULL);
    while (cmds[++i])
        temp_cmds[i] = cmds[i];
    temp_cmds[i++] = ft_strdup(str);
    temp_cmds[i] = NULL;
    free(cmds);
    return (temp_cmds);
}
