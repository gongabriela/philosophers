# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 12:13:28 by ggoncalv          #+#    #+#              #
#    Updated: 2025/04/15 12:13:28 by ggoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = philosophers.c parsing.c parsing_utils.c init_and_create.c routine.c routine_utils.c server.c time.c free.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

debug:
	cc -g $(SRC) -o $(NAME)
	gdb --tui $(NAME)

valgrind:
	valgrind --leak-check=full --track-origins=yes --tool=helgrind ./philo
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@