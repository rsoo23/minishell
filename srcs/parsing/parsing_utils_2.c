/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:56:40 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/20 08:56:40 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_input_redir(char *redir)
{
	int	redir_len;

	if (!redir)
		return (0);
	redir_len = ft_strlen(redir);
	if (!ft_strncmp(redir, "<", redir_len))
		return (1);
	else if (!ft_strncmp(redir, "<>", redir_len))
		return (1);
	return (0);
}

int	is_heredoc(char *redir)
{
	if (!redir)
		return (0);
	if (!ft_strncmp(redir, "<<", 2))
		return (1);
	return (0);
}

int	is_output_redir(char *redir)
{
	int	redir_len;

	if (!redir)
		return (0);
	redir_len = ft_strlen(redir);
	if (!ft_strncmp(redir, ">", redir_len))
		return (1);	
	else if (!ft_strncmp(redir, ">>", redir_len))
		return (2);	
	return (0);
}
