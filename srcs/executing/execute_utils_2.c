/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:58:30 by lewlee            #+#    #+#             */
/*   Updated: 2023/08/09 12:01:41 by lewlee           ###   ########.fr       */
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

