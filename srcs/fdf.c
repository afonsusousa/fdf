/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 01:53:05 by amagno-r         ###   ########.fr       */
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
	int background_color = 0x1a1a2e; 
	draw_background(data, background_color);
}

int rotate_and_render(t_data *data)
{
    static const double frame_duration_144_fps = 1.0 / 144.0;

    data->time += frame_duration_144_fps; // Increment time
	clear_image(data);
	apply_auto_rotation(data);
	apply_keys(data);
	transform(data);
	if (data->view.render_mode == RENDER_PRIORITY)
		draw_lines_priority(data);   
	else if (data->view.render_mode == RENDER_TRAVERSAL)
		draw_lines_traversal(data);  
	draw_menu_background(data, 0x3a3544);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	display_complete_menu(data);
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
	
	
	img.time = 0;
	img.view.alpha = 67.809;     
	img.view.beta = 67.809;      
	img.view.gamma = 203.427;    
	img.view.scale = 0.25;    
	img.view.zoom = 15;
	img.view.angle = 0.523599;
	img.view.brainfuck_priority = true;
	img.view.render_mode = RENDER_PRIORITY;
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
	img.view.ripple = false;
	
	img.view.axis[0] = 0.0;
	img.view.axis[1] = 0.0;
	img.view.axis[2] = 1.0;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.window_width, img.window_height, "amagno-r - FDF");
	img.mlx = mlx;
	img.mlx_win = mlx_win;
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	img.mouse.is_pressed = 0;
	img.mouse.button = 0;
	img.mouse.last_x = 0;
	img.mouse.last_y = 0;
	
	keyboard_init(&img);
	mlx_loop_hook(mlx, rotate_and_render, &img);
	mlx_hook(mlx_win, 2, 1L<<0, handle_keypress, &img);    
	mlx_hook(mlx_win, 3, 1L<<1, handle_view_keyrelease, &img);  
	mlx_mouse_hook(mlx_win, handle_mouse_scroll, &img);
	mlx_hook(mlx_win, 4, 1L<<2, handle_mouse_press, &img);
	mlx_hook(mlx_win, 5, 1L<<3, handle_mouse_release, &img);
	mlx_hook(mlx_win, 6, 1L<<6, handle_mouse_move, &img);
	mlx_loop(mlx);
}