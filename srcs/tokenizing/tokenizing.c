/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/04 13:53:50 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_wspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static void	tokenize_word(t_tok_info *info, char *s)
{
	t_tok	*new_token;
	char	*temp_tok_str;

	while (s[info->i] && !is_wspace(s[info->i]) && !is_meta_char(s[info->i]))
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

int	tokenize(t_tok_info *info, char *s)
{
	t_tok	*temp;

	info->i = 0;
	info->token_list = NULL;
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
	temp = info->token_list;
	while (temp)
	{
		temp->str = expand_tokens_and_intepret_quotes(temp->str);
		if (!temp->str)
			return (0);
		temp = temp->next;
	}
	return (1);
}
