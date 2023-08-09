# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lewlee <lewlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 00:10:03 by rsoo              #+#    #+#              #
#    Updated: 2023/08/09 12:27:19 by lewlee           ###   ########.fr        #
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
		executing/execute_utils_2\
		executing/execute_utils_2
SRCS_CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS_CFILES:.c=.o)
file_check = $(shell if [ -e readline_path.txt ]; then echo "yes"; else echo "no"; fi)

LIBFT_DIR = libft
LIBFT = libft.a

%.o: %.c ./Makefile
	@$(CC) $(CFLAGS) $(CSAN) $(READ_INC) -c $< -o $@

all: find_path $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(CSAN) $(READ_LIB) -lreadline $(OBJS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

find_path:
ifeq ($(call file_check),no)
	@echo "\033[96mFinding \033[0;93mlibreadline.a...\033[0;37m"
	@find / -name "libreadline.a" 2>/dev/null | head -n 1 > readline_path.txt
else
	@echo "\033[96mUsing existing \033[0;93mreadline_path.txt\033[0;37m"
endif

RDLINE_PATH := $(shell cat readline_path.txt)
READ_LIB = $(addprefix -L, $(subst /libreadline.a,, $(RDLINE_PATH)))
READ_INC = $(subst /lib/libreadline.a,/include, $(addprefix -I, $(RDLINE_PATH)))

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS) 

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY = RDLINE_PATH clean fclean re all
