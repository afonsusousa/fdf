/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 19:49:29 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "fdf.h"
#include <stdio.h>

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
    int lines_drawn = 0;
    
    // First pass: calculate display coordinates for all points
	for (int i = 0; i < img.map->points_count; i++)
		rotate_point(&img.map->points[i], &img.rotation);
    
    // Second pass: draw horizontal lines (connecting points in same row)
    for (int y = 0; y < img.map->map_height; y++)
    {
        for (int x = 0; x < img.map->map_width - 1; x++)
        {
            t_point *p1 = get_point(&img, x, y);
            t_point *p2 = get_point(&img, x + 1, y);
            if (p1 && p2)
            {
                // Add offset to center the image
                t_coords start = {p1->display.x + 960, p1->display.y + 540};
                t_coords end = {p2->display.x + 960, p2->display.y + 540};
                draw_line(&img, &start, &end);
                lines_drawn++;
            }
        }
    }
    
    // Third pass: draw vertical lines (connecting points in same column)
    for (int x = 0; x < img.map->map_width; x++)
    {
        for (int y = 0; y < img.map->map_height - 1; y++)
        {
            t_point *p1 = get_point(&img, x, y);
            t_point *p2 = get_point(&img, x, y + 1);
            if (p1 && p2)
            {
                // Add offset to center the image
                t_coords start = {p1->display.x + 960, p1->display.y + 540};
                t_coords end = {p2->display.x + 960, p2->display.y + 540};
                draw_line(&img, &start, &end);
                lines_drawn++;
            }
        }
    }
	
    printf("Lines drawn: %d\n", lines_drawn);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

