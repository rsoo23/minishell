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

// finds the Y axis of a char 2d array
int	array2d_y(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

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

void	get_fd(t_cmd *new_cmd, char *redir, char *file_name)
{
	if (is_input_redir(redir))
	{
		new_cmd->fd_in = open(file_name, O_RDONLY);
		new_cmd->infile_name = ft_strdup(file_name);
	}
	else if (is_output_redir(redir) == 1)
		new_cmd->fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (is_output_redir(redir) == 2)
		new_cmd->fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
}
