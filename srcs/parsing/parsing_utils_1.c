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

void	hanging_pipe(t_cmd **cmd_list, t_cmd *new_cmd, t_tok **tok_lst)
{
	char	*pending_cmd;

	new_cmd = init_cmd(1);
	pending_cmd = readline("> ");
	while (!pending_cmd[0])
		pending_cmd = readline("> ");
	new_cmd->cmds = ft_split(pending_cmd, ' ');
	add_cmd_to_back(cmd_list, new_cmd);
	delete_token(tok_lst, (*tok_lst)->str);
}

int	is_next_token_valid(t_tok **token_list, t_tok **temp)
{
	if ((*token_list)->next && !is_meta_char((*token_list)->next->str[0]))
		return (1);
	else if (!(*token_list)->next)
		ft_putstr_fd("bash: syntax error near unexpected token 'newline'\n", 2);
	else if (is_input_redir((*token_list)->next->str) \
	|| is_meta_char((*token_list)->next->str[0]))
	{
		ft_putstr_fd("bash: syntax error near unexpected token ", 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd((*token_list)->next->str, 2);
		ft_putstr_fd("'\n", 2);
		delete_token(token_list, (*token_list)->next->str);
		*temp = (*token_list);
	}
	delete_token(token_list, (*token_list)->str);
	*temp = (*token_list);
	return (0);
}
