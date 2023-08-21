/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:38:28 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/21 14:38:28 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_path(void)
{
	char	*temp;
	char	**paths;

	temp = shell_getenv("PATH");
	if (!temp)
		return (NULL);
	paths = ft_split(temp, ':');
	free(temp);
	return (paths);
}
