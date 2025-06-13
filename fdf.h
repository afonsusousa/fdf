/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 21:55:02 by amagno-r         ###   ########.fr       */
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
#include "minilibx-linux/mlx.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Key indices for continuous rotation


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
	bool paint;
	int color;
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
	bool steep;
	int z1;        
	int z2;        
	int color1;    
	int color2;    
} t_line;

typedef enum e_render_mode
{
	RENDER_PRIORITY = 0,
	RENDER_TRAVERSAL = 1
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
	bool brainfuck_priority;
	bool auto_rotate_x;
	bool auto_rotate_y;
	bool auto_rotate_z;
	bool chaos_mode;
	double	axis[3];
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
    int     map_width;
    int     map_height;
    int     points_count;  
	int		max_z;
	int		min_z;
    t_point     *points;
} t_map;

typedef struct s_mouse
{
	int is_pressed;
	int button;
	int last_x;
	int last_y;
}	t_mouse;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		window_height;
	int		window_width;
	int		menu_ratio;
	int		menu_width;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	time;
    t_map   *map;
    t_view 	view;
    t_mouse mouse; 
    int		keys[14];
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

void point_atoi(t_point *point, char *nptr);
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
void init_line_struct(t_line *line, int p0[2], int p1[2]);
void init_line(t_data *data, t_line *line, t_point *p0, t_point *p1);
void draw_background(t_data *data, int color);
void draw_menu_background(t_data *data, int color);

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
// void set_line_color(t_line *line, t_data *data, t_point *p0, t_point *p1);
void draw_pixel_color(t_data *data, int x, int y, int color, float alpha);

// Rotations

void normalize_angles(t_data *data);
void rotate_x_coords(double coords[3], double alpha);
void rotate_y_coords(double coords[3], double beta);
void rotate_z_coords(double coords[3], double gamma);
void x_transforms(t_data *data, t_point *point, double coords[3]);
void y_transforms(t_data *data, t_point *point, double coords[3]);
void z_transforms(t_data *data, t_point *point, double coords[3]);
void transform_point(t_data *data, t_point *source);
void rotate_vector(double vector[3], t_view *view);
void transform(t_data *data);

//Transforms
double ripple_height(t_data *data, t_point *point);
double wave_height(t_data *data, t_point *point);

// Float utilities
int integer_of(float n);
int round_of(float n);
float float_of(float n);
float fractional_of(float n);
float reverse_fractional_of(float n);

// Keyboard controls
void keyboard_init(t_data *data);
int handle_keypress(int keycode, t_data *data);
int handle_view_keypress(int keycode, t_data *data);
int handle_view_keyrelease(int keycode, t_data *data);
void apply_auto_rotation(t_data *data);
void apply_keys(t_data *data);

// Keyboard helper functions
int handle_effects_keys(int keycode, t_data *data);
int handle_exit_keys(int keycode);
int handle_reset_keys(int keycode, t_data *data);
int handle_rendering_keys(int keycode, t_data *data);
int handle_auto_rotation_keys(int keycode, t_data *data);
void reset_view(t_data *data);

// Mouse controls
int handle_mouse_press(int button, int x, int y, t_data *data);
int handle_mouse_release(int button, int x, int y, t_data *data);
int handle_mouse_move(int x, int y, t_data *data);
int handle_mouse_scroll(int button, int x, int y, t_data *data);

// Menu display functions
void display_rotation_info(t_data *img);
void display_view_info(t_data *img);
void display_auto_rotation_status(t_data *img);
void display_render_mode(t_data *img);
void display_menu_header(t_data *img);
void display_all_menu_info(t_data *img);

// Menu controls display
void display_basic_controls(t_data *img);
void display_mouse_controls(t_data *img);
void display_rendering_controls(t_data *img);
void display_auto_rotation_controls(t_data *img);
void display_all_controls(t_data *img);

// Main menu function
void display_complete_menu(t_data *img);

// Axis display
void display_axis_info(t_data *img);
void draw_axis_line(t_data *img, int start[2], int end[2], int color);
void project_axis_vector(double axis[3], int center[2], int end[2], t_view *view);
void draw_axis_border(t_data *img, int corner_x, int corner_y, int size);
void draw_axis_labels(t_data *img, int corner_x, int corner_y, int size);
void get_axis_position(t_data *img, int *corner_x, int *corner_y, int *size);
void init_axis_vectors(double x_axis[3], double y_axis[3], double z_axis[3]);
void draw_axis_vectors(t_data *img, int center[2], t_view *view);

#endif