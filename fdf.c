/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 15:39:23 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "fdf.h"


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
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    for (int y = 0; y < img.map->map_height; y++)
    {
        for (int x = 0; x < img.map->map_width; x++)
        {
            t_point *point = get_point(&img, x, y);
            if (point && point->z == 0)
            {
                // Draw a small red square for each zero point
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        my_mlx_pixel_put(&img, x * 20 + i + 100, y * 20 + j + 100, 0x00FF0000);
                    }
                }
            }
            else if (point && point->z != 0)
            {
                // Draw a small blue square for each non-zero point
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        my_mlx_pixel_put(&img, x * 20 + i + 100, y * 20 + j + 100, 0x0000FF00);
                    }
                }
            }
        }
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

