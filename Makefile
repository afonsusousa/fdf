# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 20:43:30 by amagno-r          #+#    #+#              #
#    Updated: 2025/06/19 00:31:30 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = fdf

# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I. -I./libft -I./minilibx-linux -I./get_next_line

# Directories
LIBFTDIR = libft
MLXDIR = minilibx-linux
GNLDIR = get_next_line

# Source files
SRCS = srcs/fdf.c \
       srcs/view/render/draw.c \
       srcs/view/render/line.c \
       srcs/view/render/line_utils.c \
       srcs/view/render/colors.c \
       srcs/view/render/render.c \
       srcs/view/gui/menu.c \
       srcs/view/gui/menu_display.c \
       srcs/view/gui/menu_display_utils.c \
       srcs/view/gui/menu_controls.c \
       srcs/view/gui/axis.c \
       srcs/view/gui/axis_utils.c \
       srcs/lines/line_priority.c \
       srcs/lines/line_priority_utils.c \
       srcs/lines/line_utils.c \
       srcs/lines/line_traversal.c \
       srcs/map/init_map.c \
       srcs/map/init_map_utils.c \
       srcs/map/init_map_read_utils.c \
       srcs/mouse/mouse.c \
       srcs/point/point.c \
       srcs/point/point_get.c \
       srcs/view/transforms/angles.c \
       srcs/view/transforms/bend.c \
       srcs/view/transforms/dvd.c \
       srcs/view/transforms/project.c \
       srcs/view/transforms/transform.c \
       srcs/view/transforms/rotations.c \
       srcs/view/transforms/ripple.c \
       srcs/view/transforms/wave.c \
       srcs/view/transforms/ortographic.c \
       srcs/utils/float_utils.c \
       srcs/utils/free.c \
       srcs/X11/keyboard.c \
       srcs/X11/keyboard_init.c \
       srcs/X11/smooth/bend.c \
       srcs/X11/smooth/scale.c \
       srcs/X11/smooth/zoom.c \
       srcs/X11/smooth/shift.c \
       srcs/X11/smooth/rotations.c \
       srcs/X11/discrete/window.c \
       srcs/X11/discrete/system.c \
       srcs/X11/discrete/rotation.c \
       srcs/X11/discrete/auto.c \
       srcs/view/view.c 

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
