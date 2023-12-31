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

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

# define DISPLAY_BUILTIN 2
# define ACTION_BUILTIN 3
# define EXIT_SHELL 4

typedef struct s_exp
{
	char	*res;
	char	*env_var;
	char	*temp;
	int		i;
	int		len;
}	t_exp;

typedef struct s_tok
{
	char			*str;
	int				in_quotes;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

typedef struct s_tok_info
{
	int		i;
	int		temp_word_len;
	t_tok	*token_list;
}	t_tok_info;

typedef struct s_cmd
{
	char			**cmds;
	char			*infile_name;
	int				fd_in;
	int				fd_out;
	int				pipe_stat;
	int				pipe[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_main
{
	char			*current_path;
	char			*user_path;
	char			*user_input;
	int				num_of_cmds;
	t_tok_info		tokens_info;
	t_cmd			*cmd_list;
	char			**envp;
	int				print_flag;
	int				exit_code;
	int				exit_code_minishell;
	struct termios	origi_attri;
	struct termios	new_attri;
}	t_main;

extern t_main	g_main;

//tokenizing.c
int		intepret_input(t_tok_info *info, char *user_input);
int		check_if_quotes_closed(char *s);

//tokenizing_utils_1.c
int		is_wspace(char c);
void	read_quote(t_tok_info *info, char *s, char q);
void	handle_single_dollar(t_exp *exp);
void	handle_exit_code(t_exp *exp);

// token_list_utils_1.c
t_tok	*init_token(char *temp_tok_str);
t_tok	*last_token(t_tok *token_list);
void	add_token_to_back(t_tok **token_list, t_tok *new_token);
void	delete_token(t_tok **token_list, char *content);
void	delete_token_list(t_tok **token_list);

// token_error_checking.c
int		token_error_checking(t_tok *tok_lst);

// expansion.c
char	*expansion(char *s);
char	*intepret_quotes(t_tok *token, char *s);
void	read_str(char *s, t_exp *exp);

// quote_handling.c
int		check_if_quotes_closed(char *s);

// parsing.c
void	parse(t_tok **tok_lst, t_cmd **cmd_lst);

// parsing_utils_1.c
void	freeing_2darray(char **s);
char	**append_cmds(char **cmds, char *str);
void	get_fd(t_cmd *new_cmd, char *redir, char *file_name);

// metachar_check.c
int		is_pipe(char *str);
int		is_meta_char(char c);
int		is_input_redir(char *redir);
int		is_output_redir(char *redir);
int		is_heredoc(char *redir);

// cmd_list_utils_1.c
t_cmd	*init_cmd(int pipe_stat);
t_cmd	*find_last_cmd(t_cmd *cmd_list);
void	add_cmd_to_back(t_cmd **cmd_list, t_cmd *new_cmd);
void	clear_cmds(t_cmd **cmd_list);

// heredoc.c
void	get_heredoc(t_cmd *new_cmd, char *limiter);

// printing_msg.c
int		end_minishell(void);
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
int		get_input(void);
char	*shell_strjoin(char const *s1, char *s2, char const *s3, int num);
char	*name_finder(char *s);
char	**array_append(char **a, char *line);
int		array2d_y(char **a);

// shell_utils2.c
int		find_char(char *s, char c);
void	print_envp(void);
void	print_export(void);
char	*merge_path(char *c);
void	cmd_clear(t_cmd **cmd_list);

// shell_utils3.c
char	**split_path(void);

// execute_utils_1.c
void	init_fds(t_cmd *lst);
int		getcmdlstlen(t_cmd *lst);
void	closing_pipes(t_cmd *cmd_list, t_cmd *cmd_node);
void	sig_init_or_end(int type);

// execute_utils_2.c
void	finishing_up_cmd(int child_amount, t_cmd *cmd_list);
void	print_exit_error_msg(char *str, int type);
void	child_init(t_cmd *cmd_node);
int		exit_func(char **cmds, int cmdlstlen);

// execute.c
int		execute(t_cmd *inst);

// main.c
void	sig_handler_child(int signum);
void	sig_handler(int signum);

#endif
