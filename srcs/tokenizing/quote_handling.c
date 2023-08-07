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
				printf("Error: single quotes unclosed\n");
			else if (q == '"')
				printf("Error: double quotes unclosed\n");
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

void	intepret_quotes_content(char *s, t_exp *exp, char q)
{
	exp->i++;
	while (s[exp->i] != q)
	{
		exp->i++;
		exp->len++;
	}
	exp->res = ft_strjoin_free_all(exp->res, \
	ft_substr(s, exp->i - exp->len, exp->len));
	exp->i++;
}

char	*intepret_quotes(char *s)
{
	t_exp	exp;

	exp.res = ft_strdup("");
	exp.env_var = NULL;
	exp.temp = NULL;
	exp.i = 0;
	while (s[exp.i])
	{
		exp.len = 0;
		if (s[exp.i] == '\'')
			intepret_quotes_content(s, &exp, '\'');
		else if (s[exp.i] == '"')
			intepret_quotes_content(s, &exp, '"');
		else
			read_str(s, &exp);
	}
	free(s);
	return (exp.res);
}
