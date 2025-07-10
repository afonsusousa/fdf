/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 23:16:57 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "lib/ft_printf/ft_printf.h"
# include "lib/libft/libft.h"
# include "lib/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define KEY_ESC		65307
# define KEY_Q			113

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				display[2];
	double			world_3d[3];
	bool			colored;
	int				color;
}					t_point;

typedef struct s_line_info
{
	t_point			*p0;
	t_point			*p1;
	float			depth;
}					t_line_info;

typedef struct s_line
{
	float			dx;
	float			dy;
	float			slope;
	int				x_start;
	int				x_end;
	float			current_y;
	bool			steep;
	int				color1;
	int				color2;
}					t_line;

typedef struct s_view
{
	int				off_x;
	int				off_y;
	double			alpha;
	double			beta;
	double			gamma;
	double			scale;
	double			angle;
	int				zoom;
}					t_view;

typedef struct s_map
{
	int				map_width;
	int				map_height;
	int				points_count;
	int				line_capacity;
	int				max_z;
	int				min_z;
	int				max_distance;
	t_point			*points;
	t_point			*center;
	t_line_info		*lines;
}					t_map;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				w_height;
	int				w_width;
	int				bits_per_pixel;
	int				endian;
	int				line_length;
	t_map			*map;
	t_view			view;
	bool			keys[16];
}					t_data;

typedef struct s_color
{
	int				color;
	float			brightness;
}					t_color;

typedef struct s_pixel_values
{
	int				y_pixel;
	float			y_fract;
	float			y_rfract;
}					t_pixel_values;

// Map initialization
void	point_atoi(t_point *point, char *nptr);
void	init_map(t_data *data, char *file_name);
void	map_set_limits(t_data *data);
void	print_map(t_data *data);
int		count_map_width(char **row);
void	get_map_dimensions(t_data *data, int map_file);
void	parse_map_row(t_data *data, char **row, int y);
void	read_map_data(t_data *data, int map_file);
void	colorize_points(t_data *data);

// Point operations
void	init_point(t_point *point, int x, int y, char *value);
void	center_coordinates(t_data *data);
t_point	*get_point(t_data *data, int x, int y);

// Window functions
void	init_window(t_data *data);
void	fdf_hooks(t_data *data);

// Main functions
void	free_data(t_data *data);
void	free_and_null(t_line_info **address);
int		rotate_and_render(t_data *img);
void	init_view(t_data *data);

// Keyboard controls
void	keyboard_init(t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_keyrelease(int keycode, t_data *data);
void	apply_keys(t_data *data);

// Keyboard helper functions
int		handle_exit_keys(t_data *data, int keycode);
int		handle_close_button(t_data *data);

// Projecting
void	rotate_x_coords(double coords[3], double alpha);
void	rotate_y_coords(double coords[3], double alpha);
void	rotate_z_coords(double coords[3], double alpha);
void	project(t_data *data, t_point *point);
void	transform_point(t_data *data, t_point *point);
void	transform(t_data *data);

// Line drawing
void	swap(int *a, int *b);
void	calculate_pixel_values(t_line *line, t_pixel_values *pixels);
int		get_interpolated_color(t_line *line, int x);
void	draw_steep(t_data *data, t_line *line);
void	draw_nonsteep(t_data *data, t_line *line);
void	draw_line_screen_only(t_data *data, t_point *p0, t_point *p1);
void	draw_line_with_offset(t_data *data, t_point *p0, t_point *p1);
void	init_line_struct(t_line *line, int p0[2], int p1[2]);
void	init_line(t_data *data, t_line *line, t_point *p0, t_point *p1);
void	draw_background(t_data *data, int color);

// Line priority and depth sorting
float	calculate_line_depth(t_line_info *line, t_view *view);
void	draw_lines_priority(t_data *data);
int		collect_horizontal_lines(t_data *data, t_line_info *lines);
int		collect_vertical_lines(t_data *data, t_line_info *lines, int start);
int		collect_lines(t_data *data, t_line_info *lines);

// Colors
int		get_color_from_z(t_data *data, t_point *point);
int		interpolate_color(int color1, int color2, float t);
void	draw_pixel_color(t_data *data, int x, int y, t_color *color);

// Line drawing
void	swap(int *a, int *b);
void	calculate_pixel_values(t_line *line, t_pixel_values *pixels);
int		get_interpolated_color(t_line *line, int x);
void	draw_steep(t_data *data, t_line *line);
void	draw_nonsteep(t_data *data, t_line *line);
void	draw_line_screen_only(t_data *data, t_point *p0, t_point *p1);
void	draw_line_with_offset(t_data *data, t_point *p0, t_point *p1);
void	init_line_struct(t_line *line, int p0[2], int p1[2]);
void	init_line(t_data *data, t_line *line, t_point *p0, t_point *p1);
void	draw_background(t_data *data, int color);

// Line priority and depth sorting
float	calculate_line_depth(t_line_info *line, t_view *view);
void	draw_lines_priority(t_data *data);
int		collect_horizontal_lines(t_data *data, t_line_info *lines);
int		collect_vertical_lines(t_data *data, t_line_info *lines, int start);
int		collect_lines(t_data *data, t_line_info *lines);

// Colors
int		get_color_from_z(t_data *data, t_point *point);
int		interpolate_color(int color1, int color2, float t);
void	draw_pixel_color(t_data *data, int x, int y, t_color *color);

int		integer_of(float n);
int		round_of(float n);
float	float_of(float n);
float	fractional_of(float n);
float	reverse_fractional_of(float n);

void	free_strs(char **strs, int n);
// merge_sort
bool	merge_sort_lines(t_line_info arr[], int low, int high);

// View initialization
void	init_view(t_data *data);
void	init_optimal_scale(t_data *data);

// Point
bool	in_screen(t_data *data, t_point *point);

// Discrete action handlers
int		handle_exit_keys(t_data *data, int keycode);
int		handle_reset_keys(int keycode, t_data *data);
int		handle_close_button(t_data *data);
#endif