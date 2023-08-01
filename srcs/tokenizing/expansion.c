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

char	*ft_strjoin_free_all(const char *s1, const char *s2)
{
	char			*res;
	unsigned int	i;
	size_t			len1;
	size_t			len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	while (i++ < len1)
		res[i - 1] = s1[i - 1];
	i = 0;
	while (i++ < len2)
		res[i - 1 + len1] = s2[i - 1];
	res[i - 1 + len1] = '\0';
	free((char *)s1);
	free((char *)s2);
	return (res);
}

void	read_single_quotes(char *str, int *i, int *word_len)
{
    if (str[*i] == '\'')
    {
        (*i)++;
        while (str[*i] && str[*i] != '\'')
        {
            (*i)++;
            (*word_len)++;
        }
    }
}

void    read_double_quotes(char *str, int *i, int *word_len)
{
    if (str[*i] == '"')
    {
        (*i)++;
        while (str[*i] && str[*i] != '"')
        {
            (*i)++;
            (*word_len)++;
        }
    }
}

char	*expand_and_intepret_quotes(char *str)
{
    char    *res;
	char	*env_var;
	char	*temp;
    int     i;
	int		len;

	res = ft_strdup("");
	env_var = NULL;
	temp = NULL;
    i = 0;
    while (str[i])
    {
    	len = 0;
		if (str[i] == '\'')
		{
			read_single_quotes(str, &i, &len);
			res = ft_strjoin_free_all(res, ft_substr(str, i - len, len));
			// printf("res1: %s$ %d %d\n", res, i-len, len);
			i++;
		}
		else if (str[i] == '"')
			i++;
        else if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != '$' 
			&& !is_wspace(str[i]) && str[i] != '"')
			{
				i++;
				len++;
			}
			temp = ft_substr(str, i - len, len);
			env_var = shell_getenv(temp);
			free(temp);
			if (!env_var)
				continue ;
			res = ft_strjoin_free_all(res, env_var);
			// printf("res3: %s$\n", res);
		}
		else
		{
			while (str[i] && str[i] != '\'' && str[i] != '$' && str[i] != '"')
			{
				i++;
				len++;
			}
			res = ft_strjoin_free_all(res, ft_substr(str, i - len, len));
			// printf("res2: %s$ %d %d\n", res, i-len, len);
		}
    }
	return (res);
}
