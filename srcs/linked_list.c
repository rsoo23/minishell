/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:32:19 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/11 09:05:40 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command   *c_new(char *c, int type)
{
	t_command   *new_c = malloc(sizeof(t_command));
	if (!new_c)
		return (NULL);
	new_c->line = c;
	new_c->type = type;
	new_c->next = NULL;
	new_c->prev = NULL;
	return (new_c);
}

t_command   *c_last(t_command *s)
{
	t_command *temp;

	temp = s;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void    c_addback(t_command **c, t_command *new)
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
  
t_command   *c_goto(t_command *c, int pos)
{
	int i;
	t_command   *temp;

	i = -1;
	temp = c;
	if (!c)
		return (NULL);
	while (++i < pos && temp->next)
		temp = temp->next;
	return (temp);
}

void    c_clear(t_command **c)
{
	t_command   *temp;

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

int c_size(t_command *c)
{
	t_command	*temp;
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
