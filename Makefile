CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread

data = philo

SRC_DIR = src
OBJ_DIR = obj

SRCS = error_message.c clean_up.c \
       input_checks.c lst_functions.c main.c parsing.c \
       tasks.c utils.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS = philo.h

$(data): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(data)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(data)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(data)

re: fclean all

.PHONY: all clean fclean re
