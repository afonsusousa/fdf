/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 19:15:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_coords
{
	int x;
	int y;
}	t_coords;

typedef  struct s_point
{
    int x;
    int y;
    int z;
	int display[2];
	int world_3d[3];
} t_point;

typedef struct s_line_info
{
	t_point *p0;
	t_point *p2;
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
	int z1;        
	int z2;        
	int color1;    
	int color2;    
} t_line;

typedef struct s_rotation
{
	double alpha;  
	double beta;   
	double gamma;  
	double scale;
	double angle;
	int zoom;     
}	t_rotation;

typedef struct s_map
{
    int     map_width;
    int     map_height;
    int     points_count;  
	int		max_z;
	int		min_z;
    t_point     *points;
} t_map;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
    t_map   *map;
    t_rotation rotation; 
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_gradient
{
	t_color start_color;
	t_color end_color;
}	t_gradient;

/* Function prototypes */

/* fdf.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/* init_map.c */
void	init_map(t_data *data, char *file_name);
void map_set_limits(t_data *data);
void print_map(t_data *data);

/* point_set.c */

void 	init_point(t_point *point, int x, int y, char *value);
void	add_point(t_data *data, int x, int y, int z);

/* point_get.c */
t_point	*get_point(t_data *data, int x, int y);

/* point.c */
void	rotate_point(t_point *source, t_rotation *rotation);
void	rotate_x_coords(double coords[3], double alpha);
void	rotate_y_coords(double coords[3], double beta);
void	rotate_z_coords(double coords[3], double gamma);
void	center_coordinates(t_data *data);

/* line_utils.c */
int		integer_of(float n);
int		round_of(float n);
float	float_of(float n);
float	fractional_of(float n);
float	reverse_fractional_of(float n);

/* line.c */
void	swap(int *a, int *b);
void	init_line_struct(t_line *line, int p0[2], int p1[2], int vz[2]);
bool	init_line(t_line *line, int p0[2], int p1[2], int vz[2]);
void	draw_line(t_data *data, t_point *p0, t_point *p1);
void	draw_line_with_offset(t_data *data, t_point *p0, t_point *p1, int offset_x, int offset_y);

void draw_horizontal(t_data *img, int offset_x, int offset_y);
void draw_vertical(t_data *img, int offset_x, int offset_y);

/* line_priority.c */
float calculate_line_depth(t_line_info *line);
int compare_depth(const void *a, const void *b);
void collect_and_render_lines(t_data *data, int offset_x, int offset_y);
void add_line_data(t_line_info *line, t_point *p0, t_point *p1);
int collect_horizontal_lines(t_data *data, t_line_info *lines);
int collect_vertical_lines(t_data *data, t_line_info *lines, int start);
int collect_lines(t_data *data, t_line_info *lines);

/* draw.c */
void	draw_pixel(t_data *data, int x, int y, float brightness);
int		get_color_from_z(int z, int min_z, int max_z);
int		interpolate_color(int color1, int color2, float t);
void	draw_pixel_color(t_data *data, int x, int y, int color, float brightness);

#endif