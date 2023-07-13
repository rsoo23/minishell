/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:50:37 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/13 14:44:37 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_tok	*get_token(char *s, int len, int tok_i)
{
	char	*temp_tok_str;
	int		i;

	temp_tok_str = malloc(len + 1);
	if (!temp_tok_str)
		return (NULL);
	i = -1;
	while (++i < len)
		temp_tok_str[i] = s[i];
	temp_tok_str[i] = '\0';
	return (init_token(temp_tok_str, tok_i));
}

static void	tokenize_word(t_tok_info *info, char *s)
{
	int		len;
	t_tok	*new_token;

	len = 0;
	while (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
	{
		info->i++;
		len++;
	}
	new_token = get_token(s + info->i - len, len, info->tok_i++);
	add_token_to_back(&info->token_list, new_token);
}

static void	tokenize_meta_char(t_tok_info *info, char *s)
{
	int		len;
	t_tok	*new_token;

	len = 0;
	while (is_meta_char(s[info->i]) && s[info->i])
	{
		info->i++;
		len++;
	}
	new_token = get_token(s + info->i - len, len, info->tok_i++);
	add_token_to_back(&info->token_list, new_token);
}

void	tokenize(t_tok_info *info, char *s)
{
	if (!s)
		return ;
	info->i = 0;
	info->tok_i = 0;
	info->token_list = NULL;
	while (s[info->i])
	{
		while (is_wspace(s[info->i]) && s[info->i])
			info->i++;
		if (!is_wspace(s[info->i]) && !is_meta_char(s[info->i]) && s[info->i])
			tokenize_word(info, s);
		while (is_wspace(s[info->i]) && s[info->i])
			info->i++;
		if (is_meta_char(s[info->i]) && s[info->i])
			tokenize_meta_char(info, s);
	}
}

void	print_tok(t_tok_info info)
{
	t_tok *temp = info.token_list;
	while (temp)
	{
		printf("%d: %s\n", temp->index, temp->str);
		temp = temp->next;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_tok_info	info;
	tokenize(&info, av[1]);
	print_tok(info);
}
