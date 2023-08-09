/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/08 15:16:16 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	tokenize_word(t_tok_info *info, char *s)
{
	t_tok	*new_token;
	char	*temp_tok_str;

	while (s[info->i] && !is_wspace(s[info->i]) && !is_meta_char(s[info->i]))
	{
		if (s[info->i] == '\'' || s[info->i] == '"')
			read_quote(info, s, s[info->i]);
		else
		{
			info->temp_word_len++;
			info->i++;
		}
	}
	temp_tok_str = \
	ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
	new_token = init_token(temp_tok_str);
	free(temp_tok_str);
	add_token_to_back(&info->token_list, new_token);
}

static void	tokenize_meta_char(t_tok_info *info, char *s)
{
	t_tok	*new_token;
	char	*temp_tok_str;

	while (is_meta_char(s[info->i]) && s[info->i])
	{
		info->i++;
		info->temp_word_len++;
	}
	temp_tok_str = \
	ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
	new_token = init_token(temp_tok_str);
	free(temp_tok_str);
	add_token_to_back(&info->token_list, new_token);
}

// void	print_tok(t_tok *token_list)
// {
// 	t_tok *temp = token_list;
// 	while (temp)
// 	{
// 		printf("%s\n", temp->str);
// 		temp = temp->next;
// 	}
// }

static void	tokenize(t_tok_info *info, char *s)
{
	while (s[info->i])
	{
		info->temp_word_len = 0;
		while (is_wspace(s[info->i]) && s[info->i])
			info->i++;
		if (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
			tokenize_word(info, s);
		else if (is_meta_char(s[info->i]) && s[info->i])
			tokenize_meta_char(info, s);
	}
}

void	intepret_quotes_in_tokens(t_tok_info *info)
{
	t_tok	*temp;

	temp = info->token_list;
	while (temp)
	{
		temp->str = intepret_quotes(temp->str);
		temp = temp->next;
	}
}

int	intepret_input(t_tok_info *info, char *s)
{
	info->i = 0;
	info->token_list = NULL;
	if (!check_if_quotes_closed(s))
		return (0);
	s = expansion(s);
	tokenize(info, s);
	intepret_quotes_in_tokens(info);
	return (1);
}
