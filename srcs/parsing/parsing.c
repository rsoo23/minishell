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
			delete_token(token_list, temp->str);
			return ;
		}
		temp = temp->next;
	}
}

void	get_redir_and_filename(t_tok **token_list, t_cmd **cmd_list, char *redir)
{
	t_tok	*temp;
	t_cmd	*new_cmd;

	temp = *token_list;
	while (temp)
	{
		if (ft_strncmp(temp->str, redir, ft_strlen(temp->str)) == 0)
		{
			temp = temp->next;
			if (!temp)
			{
				printf("%s\n", ft_strjoin(redir, " error\n"));
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

void	get_cmds(t_tok **token_list, t_cmd **cmd_list)
{
	t_tok	*temp;
	t_cmd	*new_cmd;

	temp = *token_list;
	while (temp)
	{
		new_cmd = init_cmd();
		while (temp && !is_meta_char(temp->str[0]))
		{
			new_cmd->cmds = append_cmds(new_cmd->cmds, temp->str);
			temp = temp->next;
		}
		add_cmd_to_back(cmd_list, new_cmd);
		if (!temp || !ft_strncmp(temp->str, ">", 1) || !ft_strncmp(temp->str, ">>", 2))
			break ;
		temp = temp->next;
	}
}

void	malloc_pipes(t_cmd **cmd_list)
{
	t_cmd	*temp;
	int		num_of_cmds;

	temp = *cmd_list;
	num_of_cmds = get_num_of_cmds(*cmd_list);
	while (temp)
	{
		if (temp->cmds)
		{
			temp->fd_table.pipe = malloc((num_of_cmds - 1) * sizeof(int *));
			if (!temp->fd_table.pipe)
				return ;
		}
		temp = temp->next;
	}
}

// first phase: get / arrange all tokens into the cmd_list
// second phase: initialize heredoc pipe + pipes

// CMD_LIST:
//       [< main.c] [>> outfile] [cmd1]       [cmd2]       [cmd3]
// IN  |                         fd_in        pipe[0][0]   pipe[1][0] 
// OUT |                         pipe[0][1]   pipe[1][1]   fd_out
void	parse(t_tok **token_list, t_cmd **cmd_list)
{
	get_limiter(token_list, cmd_list);
	get_redir_and_filename(token_list, cmd_list, "<");
	get_redir_and_filename(token_list, cmd_list, "<>");
	get_redir_and_filename(token_list, cmd_list, ">");
	get_redir_and_filename(token_list, cmd_list, ">>");
	get_cmds(token_list, cmd_list);
	malloc_pipes(cmd_list);
}

// void	print_tok(t_tok *token_list)
// {
// 	t_tok *temp = token_list;
// 	while (temp)
// 	{
// 		printf("%d: %s\n", temp->index, temp->str);
// 		temp = temp->next;
// 	}
// 	printf("\n");
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
// 		printf("redir: %s\n", temp->redirection);
// 		printf("file: %s\n", temp->file_name);
// 		printf("lim: %s\n", temp->limiter);
// 		temp = temp->next;
// 	}
// }

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	t_tok_info	info;
// 	t_cmd		*cmd_list;

// 	tokenize(&info, av[1]);
// 	print_tok(info.token_list);
// 	parsing(&info.token_list, &cmd_list);
// 	print_cmd_list(cmd_list);
// 	delete_all_tokens(&info.token_list);
// }
/*
cc -Wall -Wextra -Werror -fsanitize=address -ggdb tokenizing.c token_list_utils_1.c tokenizing_utils_1.c parsing.c cmd_list_utils_1.c parsing_utils_1.c ../libft/libft.a  && ./a.out "ls -la << lim | cat >> hi.txt"

*/
