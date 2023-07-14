/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:14:50 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/13 14:49:41 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_tok	*init_token(char *temp_tok_str, int tok_i)
{
	t_tok	*new_tok;
	
	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return (NULL);
	new_tok->index = tok_i;
	new_tok->str = temp_tok_str;
	new_tok->next = NULL;
	new_tok->prev = NULL;
	return (new_tok);
}

t_tok	*find_last_token(t_tok *token_list)
{
	t_tok	*temp;

	if (!token_list)
		return (NULL);
	temp = token_list;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void    add_token_to_back(t_tok **token_list, t_tok *new_token)
{
	t_tok	*last_token;
	
	if (!new_token)
		return ;
	if (!*token_list)
		*token_list = new_token;
	else
	{
		last_token = find_last_token(*token_list);
		last_token->next = new_token;
		new_token->prev = last_token;
	}
}

void    clear_tokens(t_tok **c)
{
	t_tok   *temp;

	if (!c || !*c)
		return ;
	temp = *c;
	while (*c)
	{
		temp = *c;
		*c = (*c)->next;
		free(temp->str);
		free(temp);
	}
	*c = NULL;
}

int token_list_size(t_tok *c)
{
	t_tok	*temp;
	int			i;

	if (!c)
		return (0);
	temp = c;
	i = 0;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}