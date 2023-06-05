# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 18:51:38 by mbelouar          #+#    #+#              #
#    Updated: 2023/06/05 00:00:31 by mbelouar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m
YELLOW = \033[0;33m

SRC = 	src/main.c \
		src/utils.c \
		src/routine.c \
		src/init_and_create.c \

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
RM = rm -f
OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)Compilation complete$(RESET)"

$(OBJS): %.o: %.c
	@echo "$(YELLOW)Compiling $< $(RESET)"
	@$(CC) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
