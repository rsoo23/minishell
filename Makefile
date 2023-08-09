# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 00:10:03 by rsoo              #+#    #+#              #
#    Updated: 2023/08/09 17:31:08 by rsoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CSAN = -fsanitize=address -g3 -ggdb
RM = rm -rf

SRCS_DIR = srcs/
SRCS = main \
		builtins \
		envp_func \
		printing_msg \
		shell_utils_1 \
		shell_utils_2 \
		metachar_check \
		tokenizing/tokenizing \
		tokenizing/tokenizing_utils_1 \
		tokenizing/token_list_utils_1 \
		tokenizing/expansion \
		tokenizing/quote_handling \
		parsing/parsing \
		parsing/parsing_utils_1 \
		parsing/cmd_list_utils_1 \
		parsing/heredoc \
		executing/execute \
		executing/execute_utils_1 \
		executing/execute_utils_2
SRCS_CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS_CFILES:.c=.o)
file_check = $(shell if [ -e readline_path.txt ]; then echo "yes"; else echo "no"; fi)

LIBFT_DIR = libft
LIBFT = libft.a

%.o: %.c ./Makefile
	@$(CC) $(CFLAGS) $(CSAN) $(READ_INC) -c $< -o $@

all: find_path $(NAME)

$(NAME): $(OBJS) $(RDLINE_PATH)
	@make bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(CSAN) $(READ_LIB) -lreadline $(OBJS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

find_path:
ifeq ($(call file_check),no)
	@echo "\033[96mFinding \033[0;93mlibreadline.a...\033[0;37m"
	@find / -name "libreadline.a" 2>/dev/null | head -n 1 > readline_path.txt
else
	@echo "\033[96mUsing existing \033[0;93mreadline_path.txt\033[0;37m"
endif

READ_LIB = -L/usr/local/Cellar/readline/8.2.1/lib
READ_INC = -I/usr/local/Cellar/readline/8.2.1/include

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS) 

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY = RDLINE_PATH clean fclean re all
