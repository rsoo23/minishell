/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_checking.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:40:12 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/11 09:40:12 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_any_metastr(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "<", 2))
		return (1);
	else if (!ft_strncmp(s, "<>", 3))
		return (1);
	else if (!ft_strncmp(s, "<<", 3))
		return (1);
	else if (!ft_strncmp(s, ">", 2))
		return (1);
	else if (!ft_strncmp(s, ">>", 3))
		return (1);
	else if (!ft_strncmp(s, "|", 2))
		return (1);
	return (0);
}

int	check_redir_valid(t_tok *tok_lst)
{
	if (tok_lst->next && !is_any_metastr(tok_lst->next->str))
		return (1);
	else if (tok_lst->in_quotes)
		return (1);
	else if (!tok_lst->next && !tok_lst->in_quotes)
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n"\
		, 2);
	else if (tok_lst->next && is_any_metastr(tok_lst->next->str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		ft_putstr_fd("'", 2);
		ft_putstr_fd(tok_lst->next->str, 2);
		ft_putstr_fd("'\n", 2);
	} 
	return (0);
}

int token_error_checking(t_tok *tok_lst)
{
	while (tok_lst)
	{
		if (!ft_strncmp(tok_lst->str, "", ft_strlen(tok_lst->str)) && 
			!tok_lst->prev)
			return (ft_putstr_fd("minishell: : command not found\n", 2), 0);
		else if (!ft_strncmp(tok_lst->str, "|", ft_strlen(tok_lst->str)) && 
			!tok_lst->prev && !tok_lst->in_quotes)
			return (ft_putstr_fd(
			"minishell: syntax error near unexpected token `|'\n", 2), 0);
		else if (!ft_strncmp(tok_lst->str, "||", 2))
			return (ft_putstr_fd(
			"minishell: syntax error near unexpected token `||'\n", 2), 0);
		else if (is_any_metastr(tok_lst->str) && !check_redir_valid(tok_lst))
			return (0);
		tok_lst = tok_lst->next;
	}
    return (1);
}

// << (not metastr)
// << (empty)
// << <

// 1. check if next exists || check if next str is not metastr
// 2. check if next is null || check if current is not in quotes
// 3. check if current is metastr || check if next exists || check if next is metastr
