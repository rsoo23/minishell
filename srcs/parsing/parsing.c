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

void	get_redir_and_filename(t_cmd **cmd_list, char *redir, char *file_name)
{
	t_cmd	*new_cmd;

	if (!file_name)
	{
		printf("%s\n", ft_strjoin(redir, " error\n"));
		return ;
	}
	new_cmd = init_cmd();
	new_cmd->redirection = ft_strdup(redir);
	new_cmd->file_name = ft_strdup(file_name);
	add_cmd_to_back(cmd_list, new_cmd);
}

void	get_cmds(t_tok **token_list, t_cmd **cmd_list)
{
	t_tok	*temp;
	t_cmd	*new_cmd;

	temp = *token_list;
	while (temp)
	{
		if (!is_meta_char(temp->str[0]))
		{
			new_cmd = init_cmd();
			new_cmd->cmds = append_cmds(new_cmd->cmds, temp->str);
			temp = temp->next;
			delete_token(token_list, temp->prev->str);
			while (temp && !is_pipe(temp->str))
			{
				if (!ft_strncmp(temp->str[0], "-", 1))
				{
					new_cmd->cmds = append_cmds(new_cmd->cmds, temp->str);
					temp = temp->prev;
					delete_token(token_list, temp->next->str);
				}
				temp = temp->next;
			}
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
	printf("\n");
}

static void	get_inputs(t_tok **token_list, t_cmd **cmd_list)
{
	t_tok	*temp;
	char	*str;
	char	*redir;

	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		redir = temp->str;
		if (temp->next)
			str = temp->next->str;
		if (is_heredoc(redir) || is_input_redir(redir))
		{
			if (is_heredoc(redir))
				get_heredoc(cmd_list, str);
			else
				get_redir_and_filename(cmd_list, redir, str);
			temp = temp->prev;
			delete_token(token_list, redir);
			delete_token(token_list, str);
			print_tok(*token_list);
		}
		temp = temp->next;
	}
}

static void get_outputs(t_tok **token_list, t_cmd **cmd_list)
{
	t_tok	*temp;
	char	*str;
	char	*redir;

	temp = *token_list;
	while (temp && !is_pipe(temp->str))
	{
		redir = temp->str;
		if (temp->next)
			str = temp->next->str;
		if (is_output_redir(redir))
		{
			get_redir_and_filename(cmd_list, redir, str);
			temp = temp->prev;
			delete_token(token_list, redir);
			delete_token(token_list, str);
			print_tok(*token_list);
		}
		temp = temp->next;
	}
}

void	parse(t_tok **token_list, t_cmd **cmd_list)
{
	while (*token_list)
	{
		get_inputs(token_list, cmd_list);
		get_cmds(token_list, cmd_list);
		get_outputs(token_list, cmd_list);
	}
	assign_infile_fd(*cmd_list);
	assign_outfile_fd(*cmd_list);
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
		printf("redir: %s\n", temp->redirection);
		printf("file: %s\n", temp->file_name);
		printf("lim: %s\n\n", temp->limiter);
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
	parse(&info.token_list, &cmd_list);
	print_cmd_list(cmd_list);
	delete_all_tokens(&info.token_list);
}
