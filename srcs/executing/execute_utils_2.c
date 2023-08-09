/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:58:30 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/09 12:32:53 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	finishing_up_cmd(int child_amount, t_cmd *cmd_list)
{
	int	sig;

	if (cmd_list)
		closing_pipes(cmd_list, NULL);
	while (child_amount--)
	{
		wait(&sig);
		if (WIFEXITED(sig))
			g_main.exit_code = WEXITSTATUS(sig);
		// printf("exit code %d\n", g_main.exit_code);
	}
	sig_init_or_end(1);
}

void	print_exit_error_msg(char *str)
{
	ft_putstr_fd("minishell\033[0;37m: exit: \033[0;31m", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0;37m: numeric argument required\n", 2);
}
