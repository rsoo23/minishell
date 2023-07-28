/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:16:47 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/28 23:47:39 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *s, int len)
{
	char	*r_str;
	int		i;

	i = 0;
	if (len > (int)ft_strlen(s))
		len = ft_strlen(s);
	r_str = (char *)malloc((len + 1) * sizeof(char));
	if (!r_str)
		return (NULL);
	while (s[i] && i < len)
	{
		r_str[i] = s[i];
		i++;
	}
	r_str[i] = '\0';
	return (r_str);
}

// shell_strjoin joins 3 strings together and based on the num variable
// it will free the 2nd string (cause funny multiple function in one line)
char	*shell_strjoin(char const *s1, char *s2, char const *s3, int num)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	if (!s1 || !s2 | !s3)
		return (NULL);
	string = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!string)
		return (NULL);
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	i = 0;
	while (s3[i])
		string[j++] = s3[i++];
	string[j] = '\0';
	if (num == 1)
		free(s2);
	return (string);
}

// this func compiles the current path and the "minishell" string to a nice
// string all together, it will check if the current path is the HOME path
// from the envp if it is it will compile it to "minishell: ~$"
char	*name_finder(char *s)
{
	char	*r_str;
	char	*temp;
	int		i;
	int		s_index;

	i = 0;
	temp = shell_getenv("HOME");
	if (!ft_strncmp(s, temp, ft_strlen(s) + 1))
	{
		r_str = shell_strjoin("minishell: ", \
		ft_strdup("~"), "$ ", 1);
		return (r_str);
	}
	free(temp);
	while (s[i])
		if (s[i++] == '/')
			s_index = i;
	if (i != 0)
	{
		temp = ft_strndup(s + s_index, i - s_index);
		if (!temp)
			return (NULL);
	}
	r_str = shell_strjoin("minishell: ", temp, "$ ", 1);
	return (r_str);
}

// this func creates a 2d array and copies the envp
// then it strdup the user input and saves it to the end of the newly created 
// array, then it frees the old 2d pointer
char	**array_append(char **a, char *line)
{
	char	**r_a;
	int		i;

	if (!line)
		return (a);
	if (!a)
	{
		r_a = malloc(2 * sizeof(char *));
		r_a[0] = ft_strdup(line);
		r_a[1] = NULL;
		return (r_a);
	}
	i = -1;
	r_a = malloc((array2d_y(a) + 2) * sizeof(char *));
	if (!r_a)
		return (NULL);
	while (a[++i])
		r_a[i] = a[i];
	r_a[i++] = ft_strdup(line);
	r_a[i] = NULL;
	free(a);
	return (r_a);
}
