/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:50:22 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/03 14:50:22 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_closing_quote(char *s, int *i, char q)
{
	(*i)++;
	while (s[*i] != q)
	{
		if (!s[*i])
		{
			if (q == '\'')
				printf("\033[0;31mError\033[0;37m: single quotes unclosed\n");
			else if (q == '"')
				printf("\033[0;31mError\033[0;37m: double quotes unclosed\n");
			return (0);
		}
		(*i)++;
	}
	(*i)++;
	return (1);
}

int	check_if_quotes_closed(char *s)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	while (s[i])
	{
		if (s[i] == '\'')
			status = find_closing_quote(s, &i, '\'');
		else if (s[i] == '"')
			status = find_closing_quote(s, &i, '"');
		else
			i++;
		if (!status)
			return (0);
	}
	return (1);
}

void	intepret_quotes_content(t_tok *token, char *s, t_exp *exp, char q)
{
	exp->i++;
	while (s[exp->i] != q)
	{
		exp->i++;
		exp->len++;
	}
	exp->res = ft_strjoin_free_all(exp->res, \
	ft_substr(s, exp->i - exp->len, exp->len));
	token->in_quotes = 1;
	exp->i++;
}

char	*intepret_quotes(t_tok *token, char *s)
{
	t_exp	exp;

	exp.res = ft_strdup("");
	exp.env_var = NULL;
	exp.temp = NULL;
	exp.i = 0;
	token->in_quotes = 0;
	while (s[exp.i])
	{
		exp.len = 0;
		if (s[exp.i] == '$' && (!s[exp.i + 1] || s[exp.i + 1] == '$' \
		|| s[exp.i + 1] == '"' || is_wspace(s[exp.i + 1])))
			handle_single_dollar(&exp);
		else if (s[exp.i] == '\'')
			intepret_quotes_content(token, s, &exp, '\'');
		else if (s[exp.i] == '"')
			intepret_quotes_content(token, s, &exp, '"');
		else
			read_str(s, &exp);
	}
	free(s);
	return (exp.res);
}
