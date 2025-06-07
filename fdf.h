/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 17:19:39 by amagno-r         ###   ########.fr       */
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

typedef  struct s_point
{
    int x;
    int y;
    int z;
} t_point;

typedef struct s_coords
{
	int x;
	int y;
}	t_coords;

typedef struct s_rotation
{
	double alpha;  // Rotation around X-axis (pitch)
	double beta;   // Rotation around Y-axis (yaw)
	double gamma;  // Rotation around Z-axis (roll)
	int scale;     // Zoom factor
}	t_rotation;

typedef struct s_map
{
    int     map_width;
    int     map_height;
    int     points_count;  // Track actual number of points stored
    t_point     *points;
} t_map;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
    t_map   *map;
    t_rotation rotation;  // Add rotation parameters
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

/* Function prototypes */

/* fdf.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	connect_two_points(void);

/* init_map.c */
void	init_map(t_data *data, char *file_name);
void print_map(t_data *data);

/* point_set.c */
size_t	pntlen(t_data *data);
size_t	ft_pntlcat(t_point *dest, t_point *src, size_t size);
t_point	*pntjoin(t_data *data, t_point *p1, t_point p2);
void	add_point(t_data *data, int x, int y, int z);

/* point_get.c */
t_point	*get_point(t_data *data, int x, int y);

/* point.c */
void	rotate_point(t_coords *coords, t_point *source, t_rotation *rotation);
void	rotate_x_coords(double *y, double *z, double alpha);
void	rotate_y_coords(double *x, double *z, double beta);
void	rotate_z_coords(double *x, double *y, double gamma);
void	apply_projection(t_coords *coords, double x, double y, double z);

#endif