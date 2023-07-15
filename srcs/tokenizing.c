/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/15 16:24:56 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// single quote: ' (ascii: 39)
// double quote: " (ascii: 34)
void	read_single_quotes(t_tok_info *info, char *s)
{
	// int	start_index;
	// int	end_index;

	// start_index = info->i++;
	// printf("st: %d\n", start_index);
	// while (s[info->i] != 39 && s[info->i])
	// 	info->i++;
	// end_index = info->i;
	// printf("end: %d\n", info->i);
	// if (info->literal_str)
	// {
	// 	free(info->literal_str);
	// 	info->literal_str = NULL;
	// }
	// info->temp_word_len = end_index - start_index + 1;
	// info->literal_str = ft_substr(s, start_index, info->temp_word_len);
	// printf("lit: %s\n", info->literal_str);

	// printf("reading single quotes\n");
	info->i++;
	info->temp_word_len++;
	while (s[info->i] != 39 && s[info->i])
	{
		printf("	%c\n", s[info->i]);
		if (!s[info->i])
		{
			printf("single quotes not closed\n");
			return ;
		}
		info->i++;
		info->temp_word_len++;
	}
	info->i++;
	info->temp_word_len++;
}

void	read_double_quotes(t_tok_info *info, char *s)
{
	// printf("reading double quotes\n");
	info->i++;
	info->temp_word_len++;
	while (s[info->i] != 34)
	{
		if (!s[info->i])
		{
			printf("double quotes not closed\n");
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

	info->temp_word_len = 0;
	if (s[info->i] == 39)
		read_single_quotes(info, s);
	else if (s[info->i] == 34)
		read_double_quotes(info, s);
	else
	{
		while (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
		{
			info->i++;
			info->temp_word_len++;
		}
	}
	new_token = get_token(info, s);
	add_token_to_back(&info->token_list, new_token);
}

static void	tokenize_meta_char(t_tok_info *info, char *s)
{
	t_tok	*new_token;

	info->temp_word_len = 0;
	while (is_meta_char(s[info->i]) && s[info->i])
	{
		info->i++;
		info->temp_word_len++;
	}
	new_token = get_token(info, s);
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
	tokenize(&info, av[1]);
	print_tok(info);
}
