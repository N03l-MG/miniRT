# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 08:59:28 by jgraf             #+#    #+#              #
#    Updated: 2025/03/19 18:25:55 by nmonzon          ###   ########.fr        #
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

MAKEFLAGS += --no-print-directory

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

PARSE_SRC = $(addprefix parse/, parse_main.c parse_light.c parse_plane.c parse_sphere.c parse_cylinder.c parse_utils.c parse_ambience.c parse_cam.c)
MAINTAINANCE_SRC = $(addprefix maintainance/, logging.c error.c cleanup.c)
RENDER_SRC = $(addprefix render/, render_scene.c camera.c shadows.c render_utils.c draw_window.c lighting.c reflection.c)
COLOR_SRC = $(addprefix color/, color.c)
HOOKS_SRC = $(addprefix hooks/, key_input.c translation_input.c rotation_input.c sample_input.c)
MATH_SRC = $(addprefix math/, vector.c vector2.c calculation.c)
ASSETS_SRC = $(addprefix assets/, plane.c sphere.c cylinder.c cylinder_cap.c)

SRCS = $(addprefix src/, main.c $(PARSE_SRC) $(MAINTAINANCE_SRC) $(RENDER_SRC) $(COLOR_SRC) $(HOOKS_SRC) $(MATH_SRC) $(ASSETS_SRC))
OBJ = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))

################################################################################
###############                 COMPILATION RULES                ###############
################################################################################

all: mlx_lib ft_lib message $(NAME)

$(NAME): $(OBJ)
	
	@$(CC) $(FLAGS) $^ $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@
	@printf "$(GREEN)Succesfully compiled $(NAME)!$(RESET)\n"

$(OBJECTS)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ $(LDFLAGS)
	@printf "Compiled %s\n" $<

$(OBJECTS):
	@mkdir -p $@

message:
	@printf "Compiling $(NAME)\n"

mlx_lib:
	@cd MLX42 && CMAKE_MAKE_FLAGS="--no-print-directory" cmake -B build && $(MAKE) -C build -j4

ft_lib:
	@$(MAKE) -C libft

clean:
	@printf "Cleaning project object files\n"
	@rm -rf $(OBJECTS)
	@$(MAKE) -C libft fclean
	@cd MLX42 && rm -rf build

fclean: clean
	@printf "$(GREEN)Cleaning all executables $(RESET)\n"
	@rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re