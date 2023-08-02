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

void	init_expander_struct(t_exp *exp)
{
	exp->res = ft_strdup("");
	exp->env_var = NULL;
	exp->temp = NULL;
	exp->i = 0;
}

void	read_single_quotes(char *s, t_exp *exp)
{
    if (s[exp->i] == '\'')
    {
        exp->i++;
        while (s[exp->i] && s[exp->i] != '\'')
        {
            exp->i++;
            exp->len++;
        }
    }
	exp->res = ft_strjoin_free_all(exp->res, ft_substr(s, \
	exp->i - exp->len, exp->len));
	exp->i++;
}

void	expand_env_var(char *s, t_exp *exp)
{
	exp->i++;
	while (s[exp->i] && s[exp->i] != '$' && \
	!is_wspace(s[exp->i]) && s[exp->i] != '"')
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

void	read_str(char *s, t_exp *exp)
{
	while (s[exp->i] && s[exp->i] != '\'' && s[exp->i] != '$' && s[exp->i] != '"')
	{
		exp->i++;
		exp->len++;
	}
	exp->res = ft_strjoin_free_all(exp->res, \
	ft_substr(s, exp->i - exp->len, exp->len));
}

char	*expand_and_intepret_quotes(char *str)
{
	t_exp	exp;

	init_expander_struct(&exp);
    while (str[exp.i])
    {
    	exp.len = 0;
		if (str[exp.i] == '\'')
			read_single_quotes(str, &exp);
		else if (str[exp.i] == '"')
			exp.i++;
        else if (str[exp.i] == '$')
			expand_env_var(str, &exp);
		else
			read_str(str, &exp);
	}
	return (exp.res);
}
