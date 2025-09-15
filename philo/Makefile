# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/13 11:01:05 by ggoncalv          #+#    #+#              #
#    Updated: 2025/09/13 11:01:05 by ggoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c parsing.c init.c free.c time.c actions.c philo_routine.c server_routine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

debug:
	cc -g $(SRC) -o $(NAME)
	gdb --tui $(NAME)

valgrind:
	valgrind --leak-check=full --track-origins=yes --tool=helgrind ./philo

sanitize:
	$(CC) $(CFLAGS) -fsanitize=thread -g $(SRC) -o $(NAME)
	./$(NAME) 5 1000 200 200
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@