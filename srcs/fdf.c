/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 16:41:23 by amagno-r         ###   ########.fr       */
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
	// Easy color switching - uncomment the one you want to try:
	
	// Dark Professional
	//int background_color = 0x1E1E1E; // VS Code Dark
	// int background_color = 0x2D2D30; // Visual Studio Dark
	// int background_color = 0x0D1117; // GitHub Dark
	int background_color = 0x282C34; // Atom One Dark
	
	// Blue Tones
	// int background_color = 0x0F1419; // Dark Blue-Gray
	// int background_color = 0x16213E; // Navy Blue
	// int background_color = 0x1A1A2E; // Deep Blue
	
	// Purple Tones
	// int background_color = 0x2D1B69; // Dark Purple (your current)
	// int background_color = 0x1E1E3F; // Deep Purple
	// int background_color = 0x483D8B; // Dark Slate Blue
	
	// Classic
	// int background_color = 0x000000; // Pure Black
	
	// Light Themes
	// int background_color = 0xF5F5F5; // Light Gray
	// int background_color = 0xFFFFFF; // Pure White
	
	int total_pixels = 1920 * 1080;
	int *pixel_ptr = (int *)data->addr;
	
	for (int i = 0; i < total_pixels; i++)
		pixel_ptr[i] = background_color;
}
int animation_frame = 0;

int rotate_and_render(t_data *img)
{
	
	clear_image(img);
	
	// Rotation disabled - keep values static for debugging
	img->view.gamma = 0.009 * animation_frame;
	img->view.alpha = 0.003 * animation_frame;
	img->view.beta = 0.006 * animation_frame;
	animation_frame++;
	
	rotate(img);
	
	// Choose rendering method:
	// Option 1: Logic-based traversal (no sorting, should fix clipping)
	draw_lines_priority(img);
	
	// Option 2: Depth-based priority sorting (original method)
	// collect_and_render_lines(img, offset_x, offset_y);
	
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	
	char rotation_text[256];
	sprintf(rotation_text, "Gamma: %.3f  Alpha: %.3f  Beta: %.3f", 
			img->view.gamma, img->view.alpha, img->view.beta);
	mlx_string_put(img->mlx, img->mlx_win, 20, 30, 0xFFFFFF, rotation_text);
	
	sprintf(rotation_text, "Scale: %.2f  Zoom: %d TOP_DOWN: %d", 
			img->view.scale, img->view.zoom, img->view.top_down);
	mlx_string_put(img->mlx, img->mlx_win, 20, 50, 0xFFFFFF, rotation_text);
	return (0);
}
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

    init_map(&img, "./maps/test_maps/elem2.fdf");
	print_map(&img);
	map_set_limits(&img);
	center_coordinates(&img);
	
	// Set view to the problematic angles for debugging clipping issues
	img.view.alpha = 67.809;     // Direct radian values
	img.view.beta = 67.809;      // Direct radian values
	img.view.gamma = 203.427;    // Direct radian values
	img.view.scale = 0.25;    
	img.view.zoom = 25;
	img.view.angle = 0.523599;
	img.view.offset_x = 1920/2;
	img.view.offset_y = 1080/2;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "amagno-r - FDF");
	img.mlx = mlx;
	img.mlx_win = mlx_win;
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mlx_loop_hook(mlx, rotate_and_render, &img);
	mlx_loop(mlx);
}