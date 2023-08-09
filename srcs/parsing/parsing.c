/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 10:21:44 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/26 10:21:44 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Get any commands while searching for any corresponding flags / arguments,
// assigning it into a 2d array

// ex: wc < in -l > out -w | gives: wc -l -w
void	get_cmds(t_tok **token_list, t_cmd *new_cmd)
{
	t_tok	*temp;

	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		if (temp->str && !is_meta_char(temp->str[0]))
		{
			new_cmd->cmds = append_cmds(new_cmd->cmds, temp->str);
			delete_token(token_list, temp->str);
			temp = *token_list;
			continue ;
		}
		temp = temp->next;
	}
}

static void	get_inputs(t_tok **token_list, t_cmd *new_cmd)
{
	t_tok	*temp;
	char	*redir;

	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		redir = temp->str;
		if ((is_heredoc(redir) || is_input_redir(redir)) \
		&& is_input_redir_valid(token_list, &temp))
		{
			if (is_heredoc(redir))
				get_heredoc(new_cmd, temp->next->str);
			else
				get_fd(new_cmd, redir, temp->next->str);
			delete_token(token_list, temp->next->str);
			temp = *token_list;
			delete_token(token_list, redir);
			temp = *token_list;
			continue ;
		}
		if (!temp)
			break ;
		temp = temp->next;
	}
}

static void	get_outputs(t_tok **token_list, t_cmd *new_cmd)
{
	t_tok	*temp;
	char	*redir;

	if (!(*token_list))
		return ;
	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		redir = temp->str;
		if (is_output_redir(redir) && temp->next)
		{
			get_fd(new_cmd, redir, temp->next->str);
			delete_token(token_list, temp->next->str);
			temp = *token_list;
			delete_token(token_list, redir);
			continue ;
		}
		temp = temp->next;
	}
}

// void	print_tok(t_tok *token_list)
// {
// 	t_tok *temp = token_list;
// 	while (temp)
// 	{
// 		printf("%d: %s\n", temp->index, temp->str);
// 		temp = temp->next;
// 	}
// }

// void	print_cmd_list(t_cmd *cmd_list)
// {
// 	t_cmd	*temp = cmd_list;
// 	while (temp)
// 	{
// 		int i = -1;
// 		if (temp->cmds)
// 			while (temp->cmds[++i])
// 				printf("cmd %d: %s\n", i, temp->cmds[i]);
// 		printf("fd_in: %d\n", temp->fd_in);
// 		printf("fd_out: %d\n", temp->fd_out);
// 		temp = temp->next;
// 	}
// }

void	parse(t_tok **token_list, t_cmd **cmd_list)
{
	t_cmd	*new_cmd;
	int		pipe_stat;

	new_cmd = NULL;
	pipe_stat = 0;
	while (*token_list)
	{
		new_cmd = init_cmd(pipe_stat);
		get_inputs(token_list, new_cmd);
		get_outputs(token_list, new_cmd);
		get_cmds(token_list, new_cmd);
		add_cmd_to_back(cmd_list, new_cmd);
		if (*token_list && (*token_list)->str && \
		!ft_strncmp((*token_list)->str, "|", 1) && !(*token_list)->next)
			hanging_pipe(cmd_list, new_cmd, token_list);
		else if (*token_list && (*token_list)->str && \
		!ft_strncmp((*token_list)->str, "|", 1) && (*token_list)->next)
			delete_token(token_list, (*token_list)->str);
		pipe_stat = 1;
	}
}


// int main()
// {
// 	t_tok_info	info;
// 	t_cmd		*cmd_list;

// 	tokenize(&info, readline(""));
// 	print_tok(info.token_list);
// 	cmd_list = NULL;
// 	parse(&info.token_list, &cmd_list);
// 	print_cmd_list(cmd_list);
// }
