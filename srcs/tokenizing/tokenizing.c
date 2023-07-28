/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/28 23:17:02 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_wspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

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
	if (s[info->i] == '\'')
		read_quotes(info, s, 39);
	else if (s[info->i] == '"')
		read_quotes(info, s, 34);
}

static void	tokenize_word(t_tok_info *info, char *s)
{
	t_tok	*new_token;
	char	*temp_tok_str;

	info->temp_word_len = 0;
	if (s[info->i] == '\'')
		read_quotes(info, s, 39);
	else if (s[info->i] == '"')
		read_quotes(info, s, 34);
	else
	{
		printf("reading word\n");
		while (!is_wspace(s[info->i]) && \
		!is_meta_char(s[info->i]) && s[info->i])
		{
			info->i++;
			info->temp_word_len++;
		}
	}
	temp_tok_str = \
	ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
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
	temp_tok_str = \
	ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
	new_token = init_token(temp_tok_str, info->tok_i++);
	add_token_to_back(&info->token_list, new_token);
}

void	tokenize(t_tok_info *info, char *str)
{
	char	*s;

	if (!str)
		return ;
	info->i = 0;
	info->tok_i = 0;
	info->token_list = NULL;
	s = expand_env_vars(str);
	while (s[info->i])
	{
		while (is_wspace(s[info->i]) && s[info->i])
			info->i++;
		if (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
			tokenize_word(info, s);
		if (is_meta_char(s[info->i]) && s[info->i])
			tokenize_meta_char(info, s);
	}
	free(s);
}
