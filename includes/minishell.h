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
# include <limits.h>                 // PATH_MAX
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
	int		temp_word_len;
	t_tok	*token_list;
}	t_tok_info;

typedef struct s_cmd
{
	char			**cmds;
	int				fd_in;
	int				fd_out;
	int				pipe[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_main
{
	char		*current_path;
	char		*user_path;
	char		*user_input;
	int			num_of_cmds;
	t_tok_info	tokens_info;
	t_cmd		*cmd_list;
	char		**envp;
}	t_main;

extern t_main	g_main;

//tokenizing.c
void	tokenize(t_tok_info *info, char *s);
int		is_wspace(char c);
// token_list_utils_1.c
t_tok	*init_token(char *temp_tok_str, int tok_i);
t_tok	*last_token(t_tok *token_list);
void	add_token_to_back(t_tok **token_list, t_tok *new_token);
void	delete_token(t_tok **token_list, char *content);

// parsing.c
void	parse(t_tok **token_list, t_cmd **cmd_list);
// parsing_utils_1.c
char	**append_cmds(char **cmds, char *str);
void	assign_infile_fd(t_cmd *cmd_list);
void	assign_outfile_fd(t_cmd *cmd_list);
// parsing_utils_2.c
int		is_pipe(char *str);
int		is_meta_char(char c);
int		is_input_redir(char *redir);
int		is_output_redir(char *redir);
int		is_heredoc(char *redir);
// cmd_list_utils_1.c
t_cmd	*init_cmd(void);
t_cmd	*find_last_cmd(t_cmd *cmd_list);
void	add_cmd_to_back(t_cmd **cmd_list, t_cmd *new_cmd);
void	clear_cmds(t_cmd **cmd_list);
// heredoc.c
void	get_heredoc(t_cmd *new_cmd, char *limiter);

// executing.c
int		execute(t_cmd *cmd_list);
// printing_msg.c
int		finishing_up(void);
void	print_welcome(void);
// envp_func.c
char	*shell_getenv(char *s);
void	add_to_envp(char *s);
void	remove_envp(char *s);
void	unset_envp(char *s);
char	**envp_dup(char **envp);
// builtins.c
int		changing_dir(char **arr);
void	shell_echo(char **a);
// shell_utils1.c
char	*shell_strjoin(char const *s1, char *s2, char const *s3, int num);
char	*name_finder(char *s);
char	**array_append(char **a, char *line);
int		array2d_y(char **a);
// shell_utils2.c
int		find_char(char *s, char c);
void	print_envp(void);
void	freeing_2darray(char **s);
char	*merge_path(char *c);
// void	clear_cmds(t_cmd **cmd_list);

#endif
