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
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 -lreadline
RM = rm -rf

SRCS_DIR = srcs/
SRCS = main path_finder
SRCS_CFILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS)))
OBJS = $(SRCS_CFILES:.c=.o)

LIBFT_DIR = libft
LIBFT = libft.a

%.o: %.c ./Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT_DIR)/$(LIBFT)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS) 

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY = clean fclean re all
