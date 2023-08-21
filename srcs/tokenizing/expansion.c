/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:02:00 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/28 21:02:00 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_env_var(char *s, t_exp *exp)
{
	exp->len = 0;
	exp->i++;
	while (s[exp->i] && s[exp->i] != '$' && !is_wspace(s[exp->i])
		&& s[exp->i] != '"' && s[exp->i] != '\''
		&& ft_isalnum(s[exp->i]))
	{
		exp->i++;
		exp->len++;
	}
	exp->temp = ft_substr(s, exp->i - exp->len, exp->len);
	exp->env_var = shell_getenv(exp->temp);
	free(exp->temp);
	if (!exp->env_var)
		return ;
	exp->res = ft_strjoin_free_all(exp->res, exp->env_var);
}

void	read_single_quotes(char *s, t_exp *exp)
{
	exp->i++;
	exp->len++;
	while (s[exp->i] != '\'')
	{
		exp->i++;
		exp->len++;
	}
	exp->res = ft_strjoin_free_all(exp->res, \
	ft_substr(s, exp->i - exp->len, exp->len + 1));
	exp->i++;
}

void	read_double_quotes(char *s, t_exp *exp)
{
	exp->i++;
	exp->res = ft_strjoin_gnl(exp->res, "\"");
	while (s[exp->i] != '"')
	{
		if (s[exp->i] == '$' && (!s[exp->i + 1] || s[exp->i + 1] == '$' \
		|| s[exp->i + 1] == '"' || is_wspace(s[exp->i + 1])))
			handle_single_dollar(exp);
		else if (s[exp->i] == '$' && s[exp->i + 1] != '?')
			expand_env_var(s, exp);
		else if (s[exp->i] == '$' && s[exp->i + 1] == '?')
			handle_exit_code(exp);
		else
		{
			while (s[exp->i] != '$' && s[exp->i] != '"')
			{
				exp->i++;
				exp->len++;
			}
			exp->res = ft_strjoin_free_all(exp->res, \
			ft_substr(s, exp->i - exp->len, exp->len));
		}
		exp->len = 0;
	}
	exp->i++;
	exp->res = ft_strjoin_gnl(exp->res, "\"");
}

void	read_str(char *s, t_exp *exp)
{
	while (s[exp->i] && s[exp->i] != '\'' \
	&& s[exp->i] != '$' && s[exp->i] != '"')
	{
		exp->i++;
		exp->len++;
	}
	exp->res = ft_strjoin_free_all(exp->res, \
	ft_substr(s, exp->i - exp->len, exp->len));
}

char	*expansion(char *s)
{
	t_exp	exp;

	exp.res = ft_strdup("");
	exp.env_var = NULL;
	exp.temp = NULL;
	exp.i = 0;
	while (s[exp.i])
	{
		exp.len = 0;
		if (s[exp.i] == '$' && (!s[exp.i + 1] || s[exp.i + 1] == '$' \
		|| s[exp.i + 1] == '"' || is_wspace(s[exp.i + 1])))
			handle_single_dollar(&exp);
		else if (s[exp.i] == '$' && s[exp.i + 1] == '?')
			handle_exit_code(&exp);
		else if (s[exp.i] == '$' && s[exp.i + 1] != '?')
			expand_env_var(s, &exp);
		else if (s[exp.i] == '\'')
			read_single_quotes(s, &exp);
		else if (s[exp.i] == '"')
			read_double_quotes(s, &exp);
		else
			read_str(s, &exp);
	}
	return (exp.res);
}
