# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 08:59:28 by jgraf             #+#    #+#              #
#    Updated: 2025/03/10 11:19:30 by jgraf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
LIB = libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

#	Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#	Source files
PARSE_SRC = $(addprefix parse/, parse_main.c)

SRC = $(addprefix src/, main.c $(PARSE_SRC))
OBJ = $(SRC:.c=.o)

#	Compile
all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -lreadline
	@printf "$(GREEN)Successfully compiled: $(RESET)%s\n" $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)Compiling: $(RESET)%s\n" $(notdir $<)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@printf "$(GREEN)Cleaned object files$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@rm libft/libft.a
	@printf "$(GREEN)Cleaned everything$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
