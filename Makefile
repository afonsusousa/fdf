# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 20:43:30 by amagno-r          #+#    #+#              #
#    Updated: 2025/06/20 23:12:29 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = fdf

# Compiler and flags
CC = cc
CFLAGS = -fPIE -Wall -Wextra -Werror -g 
INCLUDES = -I. -I./lib/libft -I./lib/minilibx-linux -I./lib/get_next_line -I./lib/ft_printf

# Directories
LIBFTDIR = lib/libft
MLXDIR = lib/minilibx-linux
GNLDIR = lib/get_next_line
PRINTFDIR = lib/ft_printf/

# Source files
SRCS = srcs/fdf.c \
       srcs/render/render.c \
       srcs/render/draw.c \
       srcs/render/colors.c \
       srcs/render/view.c \
       srcs/render/lines/drawing/line.c \
       srcs/render/lines/drawing/line_utils.c \
       srcs/render/lines/drawing/float_utils.c \
       srcs/render/lines/sorting/line_priority.c \
       srcs/render/lines/sorting/line_priority_utils.c \
       srcs/render/lines/sorting/line_utils.c \
       srcs/render/lines/sorting/line_traversal.c \
       srcs/gui/menu.c \
       srcs/gui/menu_display.c \
       srcs/gui/menu_display_utils.c \
       srcs/gui/menu_controls.c \
       srcs/gui/axis.c \
       srcs/gui/axis_utils.c \
       srcs/map/init_map.c \
       srcs/map/init_map_utils.c \
       srcs/map/init_map_read_utils.c \
       srcs/points/point.c \
       srcs/points/point_get.c \
       srcs/transforms/angles.c \
       srcs/transforms/bend.c \
       srcs/transforms/dvd.c \
       srcs/transforms/project.c \
       srcs/transforms/transform.c \
       srcs/transforms/rotations.c \
       srcs/transforms/ripple.c \
       srcs/transforms/wave.c \
       srcs/transforms/ortographic.c \
       srcs/transforms/geo.c \
       srcs/utils/free.c \
       srcs/X11/mouse/mouse.c \
       srcs/X11/keyboard/keyboard.c \
       srcs/X11/keyboard/smooth/bend.c \
       srcs/X11/keyboard/smooth/scale.c \
       srcs/X11/keyboard/smooth/zoom.c \
       srcs/X11/keyboard/smooth/shift.c \
       srcs/X11/keyboard/smooth/rotations.c \
       srcs/X11/keyboard/discrete/window.c \
       srcs/X11/keyboard/discrete/system.c \
       srcs/X11/keyboard/discrete/rotation.c \
       srcs/X11/keyboard/discrete/auto.c  

OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
PRINTF = $(PRINTFDIR)/libftprintf.a
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

$(NAME): $(LIBFT) $(MLX) $(PRINTF) $(OBJS) $(GNL_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C $(LIBFTDIR) --no-print-directory

$(PRINTF):
	@echo "$(BLUE)Building libft...$(RESET)"
	@make -C $(PRINTFDIR) --no-print-directory
	
$(MLX):
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@make -C $(MLXDIR) --no-print-directory

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS) $(GNL_OBJS)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@make -C $(PRINTFDIR) clean --no-print-directory
	@make -C $(MLXDIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory
	@make -C $(PRINTFDIR) fclean --no-print-directory

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
