/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 15:35:07 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef  struct s_point
{
    int x;
    int y;
    int z;
    bool last;
} t_point;

typedef struct s_map
{
    int     map_width;
    int     map_height;
    t_point     *map;
} t_map;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
    t_map   *map;
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

/* point_set.c */
size_t	pntlen(t_point *pnt);
size_t	ft_pntlcat(t_point *dest, t_point *src, size_t size);
t_point	*pntjoin(t_point *p1, t_point p2);
void	add_point(t_data *data, int x, int y, int z);

/* point_get.c */
t_point	*get_point(t_data *data, int x, int y);

#endif