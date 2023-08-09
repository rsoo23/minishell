/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:02:55 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/09 12:04:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_exit_error_msg(char *str)
{
	ft_putstr_fd("minishell\033[0;37m: exit: \033[0;31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0;37m: numeric argument required\n", 2);
}
