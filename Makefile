# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:34:18 by bgretic           #+#    #+#              #
#    Updated: 2025/04/17 20:12:11 by bgretic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Werror -Wextra

NAME = philo
HEADER = philo.h

SRC_DIR = src
OBJ_DIR = obj

SRCS = input_checks.c clean_up.c monitor.c \
       lst_functions.c main.c parsing_1.c parsing_2.c \
       utils_1.c utils_2.c tasks.c \
	   single_philos_life.c multiple_philos_life.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
