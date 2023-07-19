/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/16 11:42:36 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// single quote: ' (ascii: 39)
// double quote: " (ascii: 34)
static void	read_quotes(t_tok_info *info, char *s, char q)
{
	info->i++;
	info->temp_word_len++;
	while (s[info->i] != q)
	{
		if (!s[info->i])
		{
			printf("quotes not closed\n");
			return ;
		}
		info->i++;
		info->temp_word_len++;
	}
	info->i++;
	info->temp_word_len++;
}

static void	tokenize_word(t_tok_info *info, char *s)
{
	t_tok	*new_token;
	char	*temp_tok_str;

	info->temp_word_len = 0;
	if (s[info->i] == 39)
		read_quotes(info, s, 39);
	else if (s[info->i] == 34)
		read_quotes(info, s, 34);
	else
	{
		while (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
		{
			info->i++;
			info->temp_word_len++;
		}
	}
	temp_tok_str = ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
	new_token = init_token(temp_tok_str, info->tok_i++);
	add_token_to_back(&info->token_list, new_token);
}

static void	tokenize_meta_char(t_tok_info *info, char *s)
{
	t_tok	*new_token;
	char	*temp_tok_str;

	info->temp_word_len = 0;
	while (is_meta_char(s[info->i]) && s[info->i])
	{
		info->i++;
		info->temp_word_len++;
	}
	temp_tok_str = ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
	new_token = init_token(temp_tok_str, info->tok_i++);
	add_token_to_back(&info->token_list, new_token);
}

void	tokenize(t_tok_info *info, char *s)
{
	if (!s)
		return ;
	info->i = 0;
	info->tok_i = 0;
	info->token_list = NULL;
	while (s[info->i])
	{
		while (is_wspace(s[info->i]) && s[info->i])
			info->i++;
		if (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
			tokenize_word(info, s);
		while (is_wspace(s[info->i]) && s[info->i])
			info->i++;
		if (is_meta_char(s[info->i]) && s[info->i])
			tokenize_meta_char(info, s);
	}
}
