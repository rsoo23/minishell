# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 00:10:03 by rsoo              #+#    #+#              #
#    Updated: 2023/07/02 00:10:03 by rsoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
CSAN = -fsanitize=address -g3
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
		tokenizing/token_list_utils_1 \
		tokenizing/expansion \
		tokenizing/quote_checking \
		parsing/parsing \
		parsing/parsing_utils_1 \
		parsing/cmd_list_utils_1 \
		parsing/heredoc \
		executing/execute \
		executing/execute_utils_1 
SRCS_CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS_CFILES:.c=.o)

LIBFT_DIR = libft
LIBFT = libft.a

# getting the readline path
RDLINE_PATH := $(shell find /usr -name "readline" 2>/dev/null | grep "opt")
READ_LIB = $(addprefix -L, $(addsuffix /lib, $(RDLINE_PATH)))
READ_INC = $(addprefix -I, $(addsuffix /include, $(RDLINE_PATH)))

%.o: %.c ./Makefile
	@$(CC) $(CFLAGS) $(CSAN) $(READ_INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(CSAN) $(READ_LIB) -lreadline $(OBJS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT) $()

clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS) 

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY = RDLINE_PATH clean fclean re all
