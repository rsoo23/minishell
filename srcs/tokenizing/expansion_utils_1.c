/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_1.c                                :+:      :+:    :+:   */
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
