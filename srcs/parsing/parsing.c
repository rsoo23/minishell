/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:41:07 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/16 11:41:07 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_fd(t_cmd *new_cmd, char *redir, char *file_name)
{
	if (is_input_redir(redir))
	{
		new_cmd->fd_in = open(file_name, O_RDONLY);
		if (new_cmd->fd_in < 0)
			return ;
	}
	else if (is_output_redir(redir) == 1)
	{
		new_cmd->fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (new_cmd->fd_out < 0)
			return ;
	}
	else if (is_output_redir(redir) == 2)
	{
		new_cmd->fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (new_cmd->fd_out < 0)
			return ;
	}
}

// Get any commands while searching for any corresponding flags,
// assigning it into a 2d array

// ex: wc < in -l > out -w | gives: wc -l -w
void	get_cmds(t_tok **token_list, t_cmd *new_cmd)
{
	t_tok	*temp;

	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		if (!is_meta_char(temp->str[0]))
		{
			new_cmd->cmds = append_cmds(new_cmd->cmds, temp->str);
			delete_token(token_list, temp->str);
			temp = *token_list;
			while (temp && !is_pipe(temp->str))
			{
				if (!ft_strncmp(&temp->str[0], "-", 1))
				{
					new_cmd->cmds = append_cmds(new_cmd->cmds, temp->str);
					delete_token(token_list, temp->str);
					temp = *token_list;
					continue ;
				}
				temp = temp->next;
			}
			if (temp && !ft_strncmp(temp->str, "|", 1))
				delete_token(token_list, temp->str);
			break ;
		}
		temp = temp->next;
	}
}

void	print_tok(t_tok *token_list)
{
	t_tok *temp = token_list;
	while (temp)
	{
		printf("%d: %s\n", temp->index, temp->str);
		temp = temp->next;
	}
}

static void	get_inputs(t_tok **token_list, t_cmd *new_cmd)
{
	t_tok	*temp;
	char	*str;
	char	*redir;

	if (!(*token_list))
		return ;
	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		redir = temp->str;
		if (temp->next)
			str = temp->next->str;
		else 
			return ;
		if (is_heredoc(redir) || is_input_redir(redir))
		{
			if (is_heredoc(redir))
				get_heredoc(new_cmd, str);
			else
				get_fd(new_cmd, redir, str);
			delete_token(token_list, redir);
			delete_token(token_list, str);
			temp = *token_list;
			continue ;
		}
		temp = temp->next;
	}
}

static void get_outputs(t_tok **token_list, t_cmd *new_cmd)
{
	t_tok	*temp;
	char	*str;
	char	*redir;

	if (!(*token_list))
		return ;
	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		redir = temp->str;
		if (temp->next)
			str = temp->next->str;
		if (is_output_redir(redir))
		{
			get_fd(new_cmd, redir, str);
			delete_token(token_list, redir);
			delete_token(token_list, str);
			temp = *token_list;
			continue ;
		}
		temp = temp->next;
	}
}

void	parse(t_tok **token_list, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;

	while (*token_list)
	{
		new_cmd = init_cmd();
		get_inputs(token_list, new_cmd);
		get_outputs(token_list, new_cmd);
		get_cmds(token_list, new_cmd);
		add_cmd_to_back(cmd_list, new_cmd);
	}
}

void	print_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp = cmd_list;
	while (temp)
	{
		int i = -1;
		if (temp->cmds)
			while (temp->cmds[++i])
				printf("cmd %d: %s\n", i, temp->cmds[i]);
		printf("fd_in: %d\n", temp->fd_in);
		printf("fd_out: %d\n", temp->fd_out);
		temp = temp->next;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_tok_info	info;
	t_cmd		*cmd_list;

	tokenize(&info, av[1]);
	print_tok(info.token_list);
	cmd_list = NULL;
	parse(&info.token_list, &cmd_list);
	print_cmd_list(cmd_list);		
}
