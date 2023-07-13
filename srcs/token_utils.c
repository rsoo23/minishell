/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:23 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/13 00:09:39 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_tok   *new_token(char *c, int type)
{
	t_tok*	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return (NULL);
	new_tok->line = c;
	new_tok->type = type;
	new_tok->next = NULL;
	new_tok->prev = NULL;
	return (new_tok);
}

t_tok   *last_token(t_tok *s)
{
	t_tok *temp;

	temp = s;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void    add_token_to_back(t_tok **c, t_tok *new)
{
	if (!new)
		return ;
	if (!*c)
		*c = new;
	else
	{
		c_last(*c)->next = new;
		new->prev = c_last(*c);
	}
}
  
t_tok   *token_goto(t_tok *c, int pos)
{
	int i;
	t_tok   *temp;

	i = -1;
	temp = c;
	if (!c)
		return (NULL);
	while (++i < pos && temp->next)
		temp = temp->next;
	return (temp);
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
		free(temp->line);
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
