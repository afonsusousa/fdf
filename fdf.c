/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 17:24:23 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "fdf.h"
#include <stdio.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void connect_two_points(void)
{
	// TODO: Implement line drawing between two points
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

    init_map(&img, "./maps/test_maps/42.fdf");

	print_map(&img);
    
    img.rotation.alpha = 0.1;    // X-axis rotation (pitch) - slight tilt
    img.rotation.beta = 0.5;     // Y-axis rotation (yaw) - rotate around Y
    img.rotation.gamma = 0.1;    // Z-axis rotation (roll) - slight roll
    img.rotation.scale = 15;     // Zoom factor
    
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF - 3D Wireframe");
	img.mlx = mlx;
	img.mlx_win = mlx_win;
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    int points_drawn = 0;
    for (int y = 0; y < img.map->map_height; y++)
    {
        for (int x = 0; x < img.map->map_width; x++)
        {
            t_point *point = get_point(&img, x, y);
            if (point)
            {
                t_coords rotated_coords;
                rotate_point(&rotated_coords, point, &img.rotation);
                
                int screen_x = rotated_coords.x + 960;
                int screen_y = rotated_coords.y + 540;
                
                if (point->z == 0)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (screen_x + i >= 0 && screen_x + i < 1920 && 
                                screen_y + j >= 0 && screen_y + j < 1080)
                                my_mlx_pixel_put(&img, screen_x + i, screen_y + j, 0x00FF0000);
                        }
                    }
                    points_drawn++;
                }
                else
                {
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (screen_x + i >= 0 && screen_x + i < 1920 && 
                                screen_y + j >= 0 && screen_y + j < 1080)
                                my_mlx_pixel_put(&img, screen_x + i, screen_y + j, 0x0000FF00);
                        }
                    }
                    points_drawn++;
                }
            }
        }
    }
    printf("Points drawn: %d\n", points_drawn);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

