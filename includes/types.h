/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:45:55 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include <stdbool.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_coords
{
	int x;
	int y;
}	t_coords;

typedef struct s_point
{
	int x;
	int y;
	int z;
	int display[2];
	int world_3d[3];
	bool paint;
	int color;
}	t_point;

typedef struct s_line_info
{
	t_point *p0;
	t_point *p1;
	float depth;
}	t_line_info;

typedef struct s_line
{
	float dx;
	float dy;
	float gradient;
	int xpxl1;
	int xpxl2;
	float intersectY;
	bool steep;
	int z1;
	int z2;
	int color1;
	int color2;
}	t_line;

typedef enum e_render_mode
{
	RENDER_PRIORITY = 0,
	RENDER_BRAINFUCK_PRIORITY = 1,
	RENDER_TRAVERSAL = 2
}	t_render_mode;

typedef struct s_view
{
	int offset_x;
	int offset_y;
	double alpha;
	double beta;
	double gamma;
	double scale;
	double angle;
	int zoom;
	bool auto_rotate_x;
	bool auto_rotate_y;
	bool auto_rotate_z;
	bool chaos_mode;
	double axis[3];
	bool top_down;
	bool left_tilt;
	bool right_tilt;
	bool ripple;
	bool wave_x;
	bool wave_y;
	t_render_mode render_mode;
}	t_view;

typedef struct s_map
{
	int map_width;
	int map_height;
	int points_count;
	int max_z;
	int min_z;
	t_point *points;
}	t_map;

typedef struct s_mouse
{
	int is_pressed;
	int button;
	int last_x;
	int last_y;
}	t_mouse;

typedef struct s_data
{
	void *mlx;
	void *mlx_win;
	void *img;
	char *addr;
	int window_height;
	int window_width;
	int menu_ratio;
	int menu_width;
	int bits_per_pixel;
	int line_length;
	int endian;
	double time;
	t_map *map;
	t_view view;
	t_mouse mouse;
	int keys[14];
}	t_data;

#endif
