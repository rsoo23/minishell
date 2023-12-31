/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:14:50 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/09 12:28:31 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tok	*init_token(char *temp_tok_str)
{
	t_tok	*new_tok;

	new_tok = malloc(sizeof(t_tok));
	if (!new_tok)
		return (NULL);
	new_tok->str = ft_strdup(temp_tok_str);
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

void	add_token_to_back(t_tok **token_list, t_tok *new_token)
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

void	delete_token(t_tok **token_list, char *content)
{
	t_tok	*temp;

	temp = *token_list;
	while (temp)
	{
		if (!ft_strncmp(temp->str, content, ft_strlen(temp->str)))
		{
			if (temp->next)
				temp->next->prev = temp->prev;
			if (temp->prev)
				temp->prev->next = temp->next;
			else if (!temp->prev)
				*token_list = temp->next;
			free(temp->str);
			free(temp);
			return ;
		}
		temp = temp->next;
	}
}

void	delete_token_list(t_tok **token_list)
{
	t_tok	*temp;

	if (!token_list || !*token_list)
		return ;
	temp = *token_list;
	while (*token_list)
	{
		temp = *token_list;
		*token_list = (*token_list)->next;
		free(temp->str);
		free(temp);
	}
	*token_list = NULL;
}
