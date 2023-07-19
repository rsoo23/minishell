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
CFLAGS = -Wall -Werror -Wextra -lreadline
CSAN = -fsanitize=address -g3
RDLINE = -L /usr/local/Cellar/readline/8.2.1/lib -I /usr/local/Cellar/readline/8.2.1/include -lreadline
RM = rm -rf

SRCS_DIR = srcs/
SRCS = main builtins cmd_exec envp_func printing_msg shell_utils_1 shell_utils_2 tokenizing/tokenizing tokenizing/tokenizing_utils_1 tokenizing/token_list_utils_1 parsing/parsing parsing/parsing_utils_1 parsing/cmd_list_utils_1
SRCS_CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS_CFILES:.c=.o)

LIBFT_DIR = libft
LIBFT = libft.a

%.o: %.c ./Makefile
	$(CC) $(CFLAGS) $(CSAN) $(RDLINE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(CSAN) $(RDLINE) $^ -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS) 

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY = clean fclean re all
