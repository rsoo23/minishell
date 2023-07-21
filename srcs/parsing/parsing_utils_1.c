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

// finds the node with < or <> then opens the file to get the fd
// then finds the first cmd node and assigns in the fd to the cmd's infile_fd
void	assign_infile_fd(t_cmd *cmd_list)
{
	int	fd;

	fd = 0;
	while (cmd_list)
	{
		if (is_input_redir(cmd_list->redirection))
		{
			fd = open(cmd_list->file_name, O_RDONLY);
			if (fd < 0)
				return ;
		}
		else if (cmd_list->cmds)
			cmd_list->infile_fd = fd;
		cmd_list = cmd_list->next;
	}
}

// is_output_redir: 
// if > then return 1,
// if >> then return 2
void	assign_outfile_fd(t_cmd *cmd_list)
{
	int	fd;

	fd = 1;
	while (cmd_list)
	{
		if (is_output_redir(cmd_list->redirection) == 1)
		{
			fd = open(cmd_list->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (fd < 0)
				return ;
		}
		else if (is_output_redir(cmd_list->redirection) == 2)
		{
			fd = open(cmd_list->file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (fd < 0)
				return ;
		}
		else if (cmd_list->cmds && !cmd_list->next)
			cmd_list->outfile_fd = fd;
		cmd_list = cmd_list->next;
	}
}
