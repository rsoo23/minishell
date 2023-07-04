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
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
RM = rm -rf

SRCS_DIR = srcs/
SRCS = main
SRCS_CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS_CFILES:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C ./libft
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	make clean -C ./libft
	$(RM) $(OBJS) 

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY = clean fclean re all
