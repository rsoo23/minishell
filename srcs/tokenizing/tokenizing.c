/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/01 17:36:38 by rsoo             ###   ########.fr       */
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

	info->temp_word_len = 0;
	while (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
	{
		info->i++;
		info->temp_word_len++;
	}
	temp_tok_str = \
	ft_substr(s, info->i - info->temp_word_len, info->temp_word_len);
	new_token = init_token(temp_tok_str);
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
	new_token = init_token(temp_tok_str);
	add_token_to_back(&info->token_list, new_token);
}

void	tokenize(t_tok_info *info, char *str)
{
	char	*s;

	if (!str)
		return ;
	info->i = 0;
	info->token_list = NULL;
	s = expand_and_intepret_quotes(str);
	// printf("str after expand: %s\n", s);
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
