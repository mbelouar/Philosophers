# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbelouar <mbelouar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 18:51:38 by mbelouar          #+#    #+#              #
#    Updated: 2023/05/13 23:36:06 by mbelouar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

SRC = 	src/main.c \
		src/utils.c \

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(RED)Compiling philosophers...$(RESET)"
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)Compilation complete$(RESET)"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
