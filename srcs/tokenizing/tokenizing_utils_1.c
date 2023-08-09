/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:47:41 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/09 11:39:03 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_wspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	read_quote(t_tok_info *info, char *s, char q)
{
	info->i++;
	info->temp_word_len++;
	while (s[info->i] != q)
	{
		info->i++;
		info->temp_word_len++;
	}
	info->i++;
	info->temp_word_len++;
}

void	handle_exit_code(t_exp *exp)
{
	exp->i += 2;
	exp->res = ft_strjoin_gnl(exp->res, ft_itoa(g_main.exit_code));
}

void	handle_single_dollar(char *s, t_exp *exp)
{
	if (!s[exp->i + 1] || s[exp->i + 1] == '$' \
	|| s[exp->i + 1] == '"' || is_wspace(s[exp->i + 1]))
	{
		exp->i++;
		exp->res = ft_strjoin_gnl(exp->res, "$");
	}
}
