/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/11 00:22:32 by amagno-r         ###   ########.fr       */
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
	(void) data;
	int background_color = 0x1a1a2e; // Atom One Dark
	draw_background(data, background_color);
}
int animation_frame = 0;

int rotate_and_render(t_data *img)
{
	
	clear_image(img);
	
	// Apply auto-rotation if enabled
	apply_auto_rotation(img);
	
	rotate(img);
	
	// Choose rendering method based on priority_rendering flag:
	// if (img->view.priority_rendering)
		draw_lines_priority(img);   // Depth-based priority sorting
	// else
	// 	draw_lines_traversal(img);  // Logic-based traversal
	
	draw_menu_background(img, 0x3a3544);
	
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	
	display_complete_menu(img);
	
	return (0);
}
int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	if (argc != 2)
		return (-1);
    init_map(&img, argv[1]);
	print_map(&img);
	map_set_limits(&img);
	center_coordinates(&img);
	
	// Set view to the problematic angles for debugging clipping issues
	img.view.alpha = 67.809;     // Direct radian values
	img.view.beta = 67.809;      // Direct radian values
	img.view.gamma = 203.427;    // Direct radian values
	img.view.scale = 0.25;    
	img.view.zoom = 15;
	img.view.angle = 0.523599;
	img.view.priority_rendering = true;
	img.view.auto_rotate_x = false;
	img.view.auto_rotate_y = false;
	img.view.auto_rotate_z = false;
	img.view.chaos_mode = false;
	img.window_height = 1080;
	img.window_width = 1920;
	img.menu_ratio = 6;
	img.menu_width = img.window_width / img.menu_ratio;
	img.view.offset_x = (img.window_width + img.menu_width) / 2;
	img.view.offset_y = img.window_height/2;
	
	// Initialize axis vector
	img.map->axis[0] = 0.0;
	img.map->axis[1] = 0.0;
	img.map->axis[2] = 1.0;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.window_width, img.window_height, "amagno-r - FDF");
	img.mlx = mlx;
	img.mlx_win = mlx_win;
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	// Initialize mouse state
	img.mouse.is_pressed = 0;
	img.mouse.button = 0;
	img.mouse.last_x = 0;
	img.mouse.last_y = 0;
	
	// Set up event hooks
	mlx_loop_hook(mlx, rotate_and_render, &img);
	mlx_key_hook(mlx_win, handle_keypress, &img);
	mlx_mouse_hook(mlx_win, handle_mouse_scroll, &img);
	mlx_hook(mlx_win, 4, 1L<<2, handle_mouse_press, &img);
	mlx_hook(mlx_win, 5, 1L<<3, handle_mouse_release, &img);
	mlx_hook(mlx_win, 6, 1L<<6, handle_mouse_move, &img);
	mlx_loop(mlx);
}