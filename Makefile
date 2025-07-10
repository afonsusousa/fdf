# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 20:43:30 by amagno-r          #+#    #+#              #
#    Updated: 2025/07/11 00:30:40 by amagno-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
NAME = fdf
BONUS_NAME = fdf_bonus

# Compiler and flags
CC = clang
CFLAGS = -O3 -ffast-math -fPIE -Wall -Wextra -Werror -g

# Base includes for libraries
BASE_INCLUDES = -I. -I./lib/libft -I./lib/minilibx-linux -I./lib/get_next_line -I./lib/ft_printf

# Separate includes for mandatory and bonus
MANDATORY_INCLUDES = $(BASE_INCLUDES) -I./mandatory -I./mandatory/includes
BONUS_INCLUDES = $(BASE_INCLUDES) -I./bonus -I./bonus/includes

# Directories
LIBFTDIR = lib/libft
MLXDIR = lib/minilibx-linux
GNLDIR = lib/get_next_line
PRINTFDIR = lib/ft_printf/

# Mandatory source files
MANDATORY_SRCS = mandatory/srcs/fdf.c \
                 mandatory/srcs/render/render.c \
                 mandatory/srcs/render/draw.c \
                 mandatory/srcs/render/colors.c \
                 mandatory/srcs/render/view.c \
                 mandatory/srcs/render/lines/drawing/line.c \
                 mandatory/srcs/render/lines/drawing/line_utils.c \
                 mandatory/srcs/render/lines/drawing/float_utils.c \
                 mandatory/srcs/render/lines/sorting/line_priority.c \
                 mandatory/srcs/render/lines/sorting/line_priority_utils.c \
                 mandatory/srcs/render/lines/sorting/line_utils.c \
                 mandatory/srcs/render/project.c \
                 mandatory/srcs/render/rotations.c \
                 mandatory/srcs/map/init_map.c \
                 mandatory/srcs/map/init_map_utils.c \
                 mandatory/srcs/map/init_map_read_utils.c \
                 mandatory/srcs/points/point.c \
                 mandatory/srcs/points/point_get.c \
                 mandatory/srcs/utils/free.c \
                 mandatory/srcs/X11/x11.c

# Bonus source files  
BONUS_SRCS = bonus/srcs/fdf_bonus.c \
             bonus/srcs/render/render_bonus.c \
             bonus/srcs/render/draw_bonus.c \
             bonus/srcs/render/colors_bonus.c \
             bonus/srcs/render/view_bonus.c \
             bonus/srcs/render/lines/drawing/line_bonus.c \
             bonus/srcs/render/lines/drawing/line_utils_bonus.c \
             bonus/srcs/render/lines/drawing/float_utils_bonus.c \
             bonus/srcs/render/lines/sorting/line_priority_bonus.c \
             bonus/srcs/render/lines/sorting/line_priority_utils_bonus.c \
             bonus/srcs/render/lines/sorting/line_utils_bonus.c \
             bonus/srcs/render/lines/sorting/line_traversal_bonus.c \
             bonus/srcs/gui/menu_bonus.c \
             bonus/srcs/gui/menu_display_bonus.c \
             bonus/srcs/gui/menu_display_utils_bonus.c \
             bonus/srcs/gui/menu_controls_bonus.c \
             bonus/srcs/gui/menu_controls_effects_bonus.c \
             bonus/srcs/gui/menu_controls_system_bonus.c \
             bonus/srcs/gui/axis_bonus.c \
             bonus/srcs/gui/axis_utils_bonus.c \
             bonus/srcs/map/init_map_bonus.c \
             bonus/srcs/map/init_map_utils_bonus.c \
             bonus/srcs/map/init_map_read_utils_bonus.c \
             bonus/srcs/points/point_bonus.c \
             bonus/srcs/points/point_get_bonus.c \
             bonus/srcs/transforms/angles_bonus.c \
             bonus/srcs/transforms/bend_bonus.c \
             bonus/srcs/transforms/dvd_bonus.c \
             bonus/srcs/transforms/project_bonus.c \
             bonus/srcs/transforms/transform_bonus.c \
             bonus/srcs/transforms/rotations_bonus.c \
             bonus/srcs/transforms/ripple_bonus.c \
             bonus/srcs/transforms/wave_bonus.c \
             bonus/srcs/transforms/ortographic_bonus.c \
             bonus/srcs/transforms/polar_bonus.c \
             bonus/srcs/utils/free_bonus.c \
             bonus/srcs/X11/mouse/mouse_bonus.c \
             bonus/srcs/X11/keyboard/keyboard_bonus.c \
             bonus/srcs/X11/keyboard/smooth/bend_bonus.c \
             bonus/srcs/X11/keyboard/smooth/scale_bonus.c \
             bonus/srcs/X11/keyboard/smooth/zoom_bonus.c \
             bonus/srcs/X11/keyboard/smooth/shift_bonus.c \
             bonus/srcs/X11/keyboard/smooth/rotations_bonus.c \
             bonus/srcs/X11/keyboard/discrete/window_bonus.c \
             bonus/srcs/X11/keyboard/discrete/system_bonus.c \
             bonus/srcs/X11/keyboard/discrete/rotation_bonus.c \
             bonus/srcs/X11/keyboard/discrete/auto_bonus.c \
             bonus/srcs/X11/keyboard/discrete/effects_bonus.c \
          

# Audio source files (bonus only)
AUDIO_SRCS =  bonus/srcs/audio/audio_utils_bonus.c \
              bonus/srcs/audio/audio_bonus.c \
              bonus/srcs/audio/pulseaudio_bonus.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
AUDIO_OBJS = $(AUDIO_SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
PRINTF = $(PRINTFDIR)/libftprintf.a
MLX = $(MLXDIR)/libmlx.a
MLXFLAGS = -lXext -lX11 -lm
PULSEFLAGS = -lpulse-simple -lpulse

# Get Next Line files
GNL_SRCS = $(GNLDIR)/get_next_line.c \
           $(GNLDIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

# Rules
all: $(NAME)

# Mandatory version
$(NAME): $(LIBFT) $(MLX) $(PRINTF) $(MANDATORY_OBJS) $(GNL_OBJS)
	@echo "Linking mandatory $(NAME)..."
	@$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "✓ Mandatory $(NAME) compiled successfully!"

# Bonus version
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(MLX) $(PRINTF) $(BONUS_OBJS) $(GNL_OBJS)
	@echo "Linking bonus $(BONUS_NAME)..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(MLX) $(MLXFLAGS) -o $(BONUS_NAME)
	@echo "✓ Bonus $(BONUS_NAME) compiled successfully!"

audio: CFLAGS += -DAUDIO
audio: $(LIBFT) $(MLX) $(PRINTF) $(BONUS_OBJS) $(AUDIO_OBJS) $(GNL_OBJS)
	@echo "Linking bonus with audio support..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(AUDIO_OBJS) $(GNL_OBJS) $(LIBFT) $(PRINTF) $(MLX) $(MLXFLAGS) $(PULSEFLAGS) -o $(BONUS_NAME)
	@echo "✓ Bonus with audio compiled successfully!"

mandatory/%.o: mandatory/%.c
	@echo "Compiling mandatory $<..."
	@$(CC) $(CFLAGS) $(MANDATORY_INCLUDES) -c $< -o $@

bonus/%.o: bonus/%.c
	@echo "Compiling bonus $<..."
	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(BASE_INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFTDIR) --no-print-directory

$(PRINTF):
	@echo "Building ft_printf..."
	@make -C $(PRINTFDIR) --no-print-directory
	
$(MLX):
	@echo "Building minilibx..."
	@make -C $(MLXDIR) --no-print-directory

clean:
	@echo "Cleaning object files..."
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS) $(AUDIO_OBJS) $(GNL_OBJS)
	@make -C $(LIBFTDIR) clean --no-print-directory
	@make -C $(PRINTFDIR) clean --no-print-directory
	@make -C $(MLXDIR) clean --no-print-directory

fclean: clean
	@echo "Cleaning executables..."
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFTDIR) fclean --no-print-directory
	@make -C $(PRINTFDIR) fclean --no-print-directory

re: fclean all

re_bonus: fclean bonus

# Debug versions
debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

debug_bonus: CFLAGS += -fsanitize=address -g3
debug_bonus: $(BONUS_NAME)

.PHONY: all bonus audio clean fclean re re_bonus test test_bonus debug debug_bonus help
