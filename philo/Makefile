# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 16:34:18 by bgretic           #+#    #+#              #
#    Updated: 2025/04/19 16:25:34 by bgretic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

NAME = philo
HEADER = philo.h

OBJ_DIR = obj

SRCS = main.c \
	   MONITOR/monitor.c \
	   PARSING/input_checks.c \
	   PARSING/lst_functions.c \
	   PARSING/parsing_1.c \
	   PARSING/parsing_2.c \
	   PHILO_LIFE/multiple_philos_life.c \
	   PHILO_LIFE/single_philos_life.c \
	   PHILO_LIFE/tasks.c \
	   UTILS/clean_up.c \
	   UTILS/utils_1.c \
	   UTILS/utils_2.c \
	   UTILS/utils_3.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re