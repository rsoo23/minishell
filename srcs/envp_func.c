/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:08:13 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/08 10:34:23 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*shell_getenv(char *s)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	temp = ft_strjoin(s, "=");
	while (g_main.envp[++i])
	{
		if (!ft_strncmp(g_main.envp[i], temp, len))
		{
			free(temp);
			return (ft_substr(g_main.envp[i], len, 9999));
		}
	}
	free(temp);
	return (NULL);
}

// it first tries to find the '=' in the string given
// if its not found then it will just end there
// else it will loop through the envp and will top if the envp[i] is NULL 
// or if the current variable name on the line of envp[i] is the same with 's'
// then if it does find the same variable name then it will free that variable
// and strdup the user input and replace the line in the envp
// else if it does not find a same name then it will call de array_appen func
void	add_to_envp(char *s)
{
	int	i;
	int	pos;

	i = 0;
	pos = find_char(s, '=');
	if (pos == (int)ft_strlen(s))
		return ;
	while (g_main.envp[i] && !!ft_strncmp(s, g_main.envp[i], pos))
		i++;
	if (g_main.envp[i])
	{
		free(g_main.envp[i]);
		g_main.envp[i] = ft_strdup(s);
		return ;
	}
	g_main.envp = array_append(g_main.envp, s);
}

// this function creates a new 2d array to transfer all the pointers over
// from the current envp, it just saves the pointers to it and removes the one
// given by the user, then when it finishes it NULL terminates the array
// then it returns it
void	remove_envp(char *s)
{
	int		i;
	int		len;
	char	**r_a;
	char	*temp;

	if (!s)
		return ;
	temp = shell_getenv(s);
	if (!temp)
		return ;
	free(temp);
	r_a = malloc(array2d_y(g_main.envp) * sizeof(char *));
	if (!r_a)
		return ;
	i = -1;
	len = ft_strlen(s);
	while (g_main.envp[++i] && ft_strncmp(s, g_main.envp[i], len))
		r_a[i] = g_main.envp[i];
	free(g_main.envp[i]);
	while (g_main.envp[++i])
		r_a[i - 1] = g_main.envp[i];
	r_a[i - 1] = NULL;
	free(g_main.envp);
	g_main.envp = r_a;
}

// this function duplicates the envp
// if it fails then it will return NULL but idk what we should do in
// that case
char	**envp_dup(char **envp)
{
	char	**n_envp;
	int		i;

	i = -1;
	n_envp = malloc((array2d_y(envp) + 1) * sizeof(char *));
	if (!n_envp)
		return (NULL);
	while (envp[++i])
	{
		n_envp[i] = ft_strdup(envp[i]);
		if (!n_envp[i])
		{
			freeing_2darray(n_envp);
			return (NULL);
		}
	}
	n_envp[i] = NULL;
	return (n_envp);
}
