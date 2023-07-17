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

#include "../includes/minishell.h"

void	get_limiter(t_tok **token_list, t_cmd **cmd_list)
{
	t_tok	*temp;
	t_cmd	*new_cmd;

	temp = *token_list;
	while (temp)
	{
		if (ft_strncmp(temp->str, "<<", 2) == 0)
		{
			temp = temp->next;
			if (!temp)
			{
				printf("<< error");
				return ;
			}
			new_cmd = init_cmd();
			new_cmd->redirection = ft_strdup("<<");
			new_cmd->limiter = ft_strjoin(temp->str, "\n");
			add_cmd_to_back(cmd_list, new_cmd);
			delete_token(token_list, "<<");
			delete_token(token_list, new_cmd->limiter);
			return ;
		}
		temp = temp->next;
	}
}

void	get_filename_and_redir(t_tok **token_list, t_cmd **cmd_list, char *redir)
{
	t_tok	*temp;
	t_cmd	*new_cmd;

	temp = token_list;
	while (temp)
	{
		if (ft_strncmp(temp->str, redir, ft_strlen(redir)) == 0)
		{
			temp = temp->next;
			if (!temp)
			{
				printf(ft_strjoin(redir, " error\n"));
				return ;
			}
			new_cmd = init_cmd();
			new_cmd->redirection = ft_strdup(redir);
			new_cmd->file_name = ft_strdup(temp->str);
			add_cmd_to_back(cmd_list, new_cmd);
			delete_token(token_list, redir);
			delete_token(token_list, new_cmd->file_name);
			return ;
		}
		temp = temp->next;
	}
}

void	parsing(t_tok *token_list, t_cmd *cmd_list)
{
	get_limiter(&token_list, &cmd_list);
	get_filename_and_redir(&token_list, &cmd_list, "<");
	get_filename_and_redir(&token_list, &cmd_list, ">");
	get_filename_and_redir(&token_list, &cmd_list, ">>");
}

void	print_tok(t_tok_info info)
{
	t_tok *temp = info.token_list;
	while (temp)
	{
		printf("%d: %s\n", temp->index, temp->str);
		temp = temp->next;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_tok_info	info;
	t_cmd		*cmd_list;

	tokenize(&info, av[1]);
	print_tok(info);
	parsing(info.token_list, cmd_list);
}
