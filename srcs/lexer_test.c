/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:02:31 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/12 15:05:30 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	op_check(char *c)
{
	if ((*c == '>') || (*c == '<') || (*c == '>' && c[1] == '>'))
		return (3);
	else if (*c == '<' && c[1] == '<')
		return (4);
	else if (*c == '|')
		return (6);
	return (0);
}

void	list_create(t_command **list, char *s)
{
	int	i;
	int j;
	int k;

	i = -1;
	j = 0;
	k = 0;
	if (!s)
		return ;
	while (++i < (int)ft_strlen(s) + 1)
	{
		if ((s[i] == 32 || s[i] == '\0') && k != 0)
		{
			c_addback(list, c_new(ft_strndup(s + (i - k), k), op_check(s + (i - k))));
			k = 0;
		}
		else if (s[i] != 32)
			k++;
	}
}

void	print_lex(t_command *l)
{
	t_command *temp = l;
	while (temp->next)
	{
		printf("%s ", temp->line);
		printf("%d\n", temp->type);
		temp = temp->next;
	}
	
}

int main(int ac, char **av)
{
	//if (ac != 2)
	//	return (1);
	t_command *list = NULL;
	list_create(&list, "lmao this is a great command | >> .. ..>>> <<   < <");
	print_lex(list);
	
	return (0);
}