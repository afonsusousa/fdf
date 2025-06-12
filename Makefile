# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 20:43:30 by amagno-r          #+#    #+#              #
#    Updated: 2025/06/12 21:06:31 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = fdf

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I. -I./libft -I./minilibx-linux -I./get_next_line

# Directories
LIBFTDIR = libft
MLXDIR = minilibx-linux
GNLDIR = get_next_line

# Source files
SRCS = srcs/fdf.c \
       srcs/draw/wireframe/draw.c \
       srcs/draw/wireframe/line.c \
       srcs/draw/wireframe/colors.c \
       srcs/gui/menu.c \
       srcs/gui/menu_display.c \
       srcs/gui/menu_controls.c \
       srcs/gui/axis.c \
       srcs/gui/axis_utils.c \
       srcs/lines/line_priority.c \
       srcs/lines/line_utils.c \
       srcs/lines/line_traversal.c \
       srcs/map/init_map.c \
       srcs/map/init_map_utils.c \
       srcs/point/point.c \
       srcs/point/point_get.c \
       srcs/point/point_set.c \
       srcs/transforms/rotate.c \
       srcs/transforms/rotations.c \
       srcs/utils/float_utils.c \
       srcs/keyboard/keyboard.c \
       srcs/keyboard/keyboard_init.c \
       srcs/keyboard/keyboard_auto.c \
       srcs/keyboard/keyboard_press.c \
       srcs/keyboard/keyboard_release.c \
       srcs/keyboard/keyboard_continuous.c \
       srcs/keyboard/keyboard_system.c \
       srcs/mouse/mouse.c

OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLXDIR)/libmlx.a
MLXFLAGS = -lXext -lX11 -lm

# Get Next Line files
GNL_SRCS = $(GNLDIR)/get_next_line.c \
           $(GNLDIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(GNL_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C $(LIBFTDIR) --no-print-directory

$(MLX):
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@make -C $(MLXDIR) --no-print-directory

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(GNL_OBJS)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@make -C $(MLXDIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory

re: fclean all

# Test with a sample map
test: $(NAME)
	@echo "$(GREEN)Running test with 42.fdf...$(RESET)"
	@./$(NAME) maps/test_maps/42.fdf

# Debug version
debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

# Help
help:
	@echo "$(BLUE)Available targets:$(RESET)"
	@echo "  all       - Build the project"
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove object files and executable"
	@echo "  re        - Rebuild the project"
	@echo "  test      - Run test with sample map"
	@echo "  debug     - Build with debug flags"
	@echo "  help      - Show this help"

.PHONY: all clean fclean re test debug help