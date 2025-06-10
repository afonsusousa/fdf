/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 16:38:55 by amagno-r         ###   ########.fr       */
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
	int z1;        
	int z2;        
	int color1;    
	int color2;    
} t_line;

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
	bool top_down;   
}	t_view;

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
    t_view view; 
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

// Function prototypes

// Main functions
void clear_image(t_data *data);
int rotate_and_render(t_data *img);

// Map initialization
void init_map(t_data *data, char *file_name);
void map_set_limits(t_data *data);
void print_map(t_data *data);
int count_map_width(char **row);
void get_map_dimensions(t_data *data, int map_file);
void parse_map_row(t_data *data, char **row, int y);
void read_map_data(t_data *data, int map_file);

// Point operations
void init_point(t_point *point, int x, int y, char *value);
void center_coordinates(t_data *data);
t_point *get_point(t_data *data, int x, int y);

// Line drawing
void swap(int *a, int *b);
void draw_steep(t_data *data, t_line *line);
void draw_nonsteep(t_data *data, t_line *line);
void draw_line(t_data *data, t_point *p0, t_point *p1);
void draw_line_with_offset(t_data *data, t_point *p0, t_point *p1);
void init_line_struct(t_line *line, int p0[2], int p1[2], int vz[2]);
bool init_line(t_line *line, int p0[2], int p1[2], int vz[2]);

// Line priority and depth sorting
float calculate_line_depth(t_line_info *line, t_view *view);
int compare_depth(const void *a, const void *b);
void draw_lines_priority(t_data *data);
void add_line_data(t_line_info *line, t_point *p0, t_point *p1);
int collect_horizontal_lines(t_data *data, t_line_info *lines);
int collect_vertical_lines(t_data *data, t_line_info *lines, int start);
int collect_lines(t_data *data, t_line_info *lines);

// Line traversal (logic-based rendering)
void draw_lines_traversal(t_data *data);

// Colors
int get_color_from_z(int z_value, int min_z, int max_z);
int interpolate_color(int color1, int color2, float t);
void set_line_color(t_line *line, t_data *data);
void draw_pixel_color(t_data *data, int x, int y, int color, float alpha);

// Rotations
void rotate_x_coords(double coords[3], double alpha);
void rotate_y_coords(double coords[3], double beta);
void rotate_z_coords(double coords[3], double gamma);
void rotate_point(t_point *source, t_view *view);
void rotate_vector(double vector[3], t_view *view);
void rotate(t_data *data);

// Float utilities
int integer_of(float n);
int round_of(float n);
float float_of(float n);
float fractional_of(float n);
float reverse_fractional_of(float n);

#endif