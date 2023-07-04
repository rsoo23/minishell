/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 00:10:23 by rsoo              #+#    #+#             */
/*   Updated: 2023/07/02 00:10:23 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>                  // perror
#include <fcntl.h>                  // open
// #include <limits.h>                 // PATH_MAX
#include <stdlib.h>                 // malloc, free
#include <stdio.h>                  // printf
#include <string.h>                 // strerror
#include <unistd.h>                 // write, access, close, fork, execve, dup, dup2, pipe, unlink

#include <dirent.h>                 // opendir, readdir, closedir
#include <readline/readline.h>      // readline
#include <readline/history.h>       // add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
#include <signal.h>                 // signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>               // stat, lstat, fstat
#include <sys/types.h>              // variables
#include <sys/wait.h>               // wait, waitpid, wait3, wait4
#include <termios.h>                // tcsetattr, tcgetattr





#endif
