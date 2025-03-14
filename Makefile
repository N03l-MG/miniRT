# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 08:59:28 by jgraf             #+#    #+#              #
#    Updated: 2025/03/14 17:40:35 by nmonzon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
###############                     BUILD SETUP                  ###############
################################################################################

NAME = miniRT
CC = cc
FLAGS = -Wall -Wextra -Werror -flto -Ofast -march=native -MMD -MP $(addprefix -I, $(INCLUDES))
LDFLAGS = -flto #-fsanitize=address
LIBFT = ./libft/libft.a
MLX = ./MLX42/build/libmlx42.a
# Colors
GREEN = \033[0;32m
RESET = \033[0m

ifeq ($(shell uname), Darwin)
	MLX_FLAGS = -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
else ifeq ($(shell uname), Linux)
	MLX_FLAGS = -L./MLX42/build -lglfw -ldl -pthread -lm
endif

################################################################################
###############                     DIRECTORIES                  ###############
################################################################################

INCLUDES = ./include ./libft ./MLX42/include/MLX42
SOURCES = ./src
OBJECTS = _obj

vpath %.h $(INCLUDES)
vpath %.c $(SOURCES)

################################################################################
###############                    SOURCE FILES                  ###############
################################################################################

SRCS = main.c \
	   parse/parse_main.c parse/parse_light.c parse/parse_plane.c parse/parse_sphere.c \
	   parse/parse_cylinder.c parse/parse_utils.c parse/parse_ambience.c parse/parse_cam.c \
	   maintainance/logging.c maintainance/error.c maintainance/cleanup.c \
	   render/render_scene.c render/camera.c \
	   color/color.c \
	   hooks/key_input.c \
	   math/vector.c \
	   assets/sphere.c

OBJ = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))

################################################################################
###############                 COMPILATION RULES                ###############
################################################################################

all: mlx_lib ft_lib $(NAME)

$(NAME): $(OBJ)
	@printf "$(GREEN)Compiling $(NAME) $(RESET)\n"
	@$(CC) $(FLAGS) $^ $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@

$(OBJECTS)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJECTS):
	@mkdir -p $@

mlx_lib:
	@cd MLX42 && cmake -B build && make -C build -j4

ft_lib:
	@$(MAKE) -C libft

clean:
	@printf "$(GREEN)Cleaning project object files $(RESET)\n"
	@rm -rf $(OBJECTS)
	@$(MAKE) -C libft fclean
	@cd MLX42 && rm -rf build

fclean: clean
	@printf "$(GREEN)Cleaning all executables $(RESET)\n"
	@rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re