/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:05:40 by lewlee            #+#    #+#             */
/*   Updated: 2023/07/19 10:37:32 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// frees the envp(thats the only one we malloced)
// then it prints out the end msg
int	finishing_up(void)
{
	freeing_2darray(g_main.envp);
	printf("\n\033[96m╔═════════════════════════════════════");
	printf("═══════════════════════════════════════════╗\n");
	printf("║                              \033[0;37m*  prog");
	printf("ram ended  *                               \033[96m║\n");
	printf("╚═══════════════════════════════════════════");
	printf("═════════════════════════════════════╝\033[0;37m\n\n");
	return (0);
}

// prints the 2nd part of the welcome msg
static void	print_welcome1(void)
{
	printf("║      \033[0;37m ████╗░████║██║████╗░██║██║");
	printf("██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░       \033[96m║\n");
	printf("║      \033[0;37m ██╔████╔██║██║██╔██╗██║██║");
	printf("╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░       \033[96m║\n");
	printf("║      \033[0;37m ██║╚██╔╝██║██║██║╚████║██║");
	printf("░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░       \033[96m║\n");
	printf("║      \033[0;37m ██║░╚═╝░██║██║██║░╚███║██║");
	printf("██████╔╝██║░░██║███████╗███████╗███████╗       \033[96m║\n");
	printf("║      \033[0;37m ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝");
	printf("╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝       \033[96m║\n");
	printf("║                                           ");
	printf("                                     ║\n");
	printf("╚═══════════════════════════════════════════");
	printf("═════════════════════════════════════╝\n\n");
}

void	print_welcome(void)
{
	printf("\033[96m╔═════════════════════════════════════");
	printf("═══════════════════════════════════════════╗\n");
	printf("║                                             ");
	printf("                                   ║\n");
	printf("║                          \033[0;37mA project");
	printf(" brought to you by                           \033[96m║\n");
	printf("║                              \033[0;37mRsoo ");
	printf("   &&    Lewlee                              \033[96m║\n");
	printf("║                                             ");
	printf("                                   ║\n");
	printf("║      \033[0;37m ███╗░░░███╗██╗███╗░░██╗██╗");
	printf("░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░       \033[96m║\n");
	print_welcome1();
}