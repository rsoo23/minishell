/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/13 00:14:56 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	tokenize(t_tok **list, char *s)
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

void	create_token()
{
	
}

void	tokenize(t_tok **tokens, char *s)
{
	char	*token;
	int		token_len;

	if ((!*s))
		return ;
	while (*s)
	{
		while (is_wspace(*s))
			s++;
		create_token(tokens, s);	
		add_token_to_back();
		// len = 0;
		// while (!is_wspace(*s))
		// {
		// 	s++;
		// 	tok_len++;
		// }
		// token = malloc()
	}
}

/*
tokenizer
1. receives string, ex: (  ls -la | grep files | wc -l  )
2. while s[i]
*/

void	print_tok(t_tok *l)
{
	t_tok *temp = l;
	while (temp->next)
	{
		printf("%s ", temp->line);
		printf("%d\n", temp->type);
		temp = temp->next;
	}
	
}

int main(int ac, char **av)
{
	(void)ac;
	t_tok	*tokens;
	tokenize(&tokens, av[1]);
	print_tok(list);
	return (0);
}