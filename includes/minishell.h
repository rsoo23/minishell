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

# include "../libft/libft.h"

# include <errno.h>                  // perror
# include <fcntl.h>                  // open
// # include <limits.h>                 // PATH_MAX
# include <stdlib.h>                 // malloc, free
# include <stdio.h>                  // printf
# include <string.h>                 // strerror
# include <unistd.h>                 // write, access, close, fork, execve, dup, dup2, pipe, unlink

# include <dirent.h>                 // opendir, readdir, closedir
# include <readline/readline.h>      // readline -> in stdio?
# include <readline/history.h>       // add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <signal.h>                 // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>               // stat, lstat, fstat
# include <sys/types.h>              // variables
# include <sys/wait.h>               // wait, waitpid, wait3, wait4
# include <termios.h>                // tcsetattr, tcgetattr

typedef struct s_tok
{
    int				index;
	char			*str;	
	struct  s_tok   *next;
    struct  s_tok   *prev;
}   t_tok;

typedef struct s_tok_info
{
	int		i;
	int		tok_i;
	t_tok	*token_list;
}	t_tok_info;

// path_finder.c
char    *merge_path(char *c, char **envp);
char    **getting_paths(char **envp);
void	freeing_2darray(char **s);

// token_list_utils_1.c
t_tok	*init_token(char *temp_tok_str, int tok_i);
t_tok	*last_token(t_tok *s);
void	add_token_to_back(t_tok **c, t_tok *new);
void	clear_tokens(t_tok **c);
int		token_list_size(t_tok *c);

// tokenizing_utils_1.c
int		is_meta_char(char c);
int		is_wspace(char c);

#endif
