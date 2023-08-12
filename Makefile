# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 00:10:03 by rsoo              #+#    #+#              #
#    Updated: 2023/08/11 09:40:46 by rsoo             ###   ########.fr        #
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
		tokenizing/token_error_checking \
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

LIBFT_DIR = libft
LIBFT = libft.a

%.o: %.c ./Makefile
	@$(CC) $(CFLAGS) $(CSAN) $(READ_INC) -c $< -o $@


all: find_path $(NAME)

find_path:
ifeq ($(wildcard readline_path.txt),)
	@echo "\033[96mFinding \033[0;93mlibreadline.a...\033[0;37m"
	@find / -name "libreadline.a" 2>/dev/null | head -n 1 > readline_path.txt
else
	@echo "\033[96mUsing existing \033[0;93mreadline_path.txt\033[0;37m"
endif
RDLINE_PATH = $(shell cat readline_path.txt 2> /dev/null | tr '\n' ' ')
READ_LIB = $(addprefix -L, $(subst /libreadline.a,, $(RDLINE_PATH)))
READ_INC = $(addprefix -I, $(subst /lib/libreadline.a,/include, $(RDLINE_PATH)))

$(NAME): $(OBJS) $(RDLINE_PATH)
	@make bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(CSAN) $(READ_LIB) -lreadline $(OBJS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)


clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS) 

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY = clean fclean re all 
