/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 03:30:50 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void clear_image(t_data *data)
{
	memset(data->addr, 0, 1920 * 1080 * (data->bits_per_pixel / 8));
}

t_point *original_points = NULL;
int animation_frame = 0;

int rotate_and_render(t_data *img)
{
	const int offset_x = 1920/2;
	const int offset_y = 1080/2;
	clear_image(img);
	if (original_points)
	{
		for (int i = 0; i < img->map->points_count; i++)
		{
			img->map->points[i].x = original_points[i].x;
			img->map->points[i].y = original_points[i].y;
			img->map->points[i].z = original_points[i].z;
		}
	}
//	img->rotation.angle = 0.523599 + sin(animation_frame * 0.02) * 0.3; // Oscillate around 30°
	img->rotation.gamma = 0.005 * animation_frame;
	img->rotation.alpha = 0.001 * animation_frame;
	animation_frame++;
	
	for (int i = 0; i < img->map->points_count; i++)
		rotate_point(&img->map->points[i], &img->rotation);
	draw_vertical(img, offset_x, offset_y);
	draw_horizontal(img, offset_x, offset_y);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

    init_map(&img, "./maps/test_maps/mars.fdf");
	print_map(&img);
	map_set_limits(&img);
	center_coordinates(&img);
	
    img.rotation.alpha = 0.0;    
    img.rotation.beta = 0.0; 
    img.rotation.gamma = 0.0;    
    img.rotation.scale = 1;    
	img.rotation.zoom = 15;
	img.rotation.angle = 0.523599;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "amagno-r - FDF");
	img.mlx = mlx;
	img.mlx_win = mlx_win;
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	original_points = malloc(img.map->points_count * sizeof(t_point));
	if (!original_points)
		return (1);
	for (int i = 0; i < img.map->points_count; i++)
	{
		original_points[i].x = img.map->points[i].x;
		original_points[i].y = img.map->points[i].y;
		original_points[i].z = img.map->points[i].z;
	}
	mlx_loop_hook(mlx, rotate_and_render, &img);
	mlx_loop(mlx);
}