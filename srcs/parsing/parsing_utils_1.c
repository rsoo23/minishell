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

#include "../../includes/minishell.h"

// theres one in shell_utils1.c
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

int get_num_of_cmds(t_cmd *cmd_list)
{
    int num_of_cmds;

    num_of_cmds = 0;
    while (cmd_list)
	{
		if (cmd_list->cmds)
			num_of_cmds++;
		cmd_list = cmd_list->next;
	}
    return (num_of_cmds);
}

int	is_input_redir(char *redir)
{
	int	redir_len;

	redir_len = ft_strlen(redir);
	if (!ft_strncmp(redir, "<", redir_len))
		return (1);	
	else if (!ft_strncmp(redir, "<<", redir_len))
		return (1);	
	else if (!ft_strncmp(redir, "<>", redir_len))
		return (1);
	return (0);
}

int	is_output_redir(char *redir)
{
	int	redir_len;

	redir_len = ft_strlen(redir);
	if (!ft_strncmp(redir, ">", redir_len))
		return (1);	
	else if (!ft_strncmp(redir, ">>", redir_len))
		return (1);	
	return (0);
}
