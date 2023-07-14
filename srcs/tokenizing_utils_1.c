/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:15:22 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/13 13:15:22 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_single_quotes(t_tok_info *info, char *s)
{
	info->i++;
	info->temp_word_len++;
	while (s[info->i] != 39)
	{
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

int	is_meta_char(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_wspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}
