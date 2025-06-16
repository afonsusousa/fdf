/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 03:02:52 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	fdf_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, rotate_and_render, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, handle_view_keyrelease, data);
	mlx_mouse_hook(data->mlx_win, handle_mouse_scroll, data);
	mlx_hook(data->mlx_win, 4, 1L << 2, handle_mouse_press, data);
	mlx_hook(data->mlx_win, 5, 1L << 3, handle_mouse_release, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, handle_mouse_move, data);
	mlx_loop(data->mlx);
}

void	init_window(t_data *data)
{
	data->window_height = 1080;
	data->window_width = 1920;
	data->menu_ratio = 6;
	data->menu_width = data->window_width / data->menu_ratio;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->window_width,
			data->window_height, "amagno-r - FDF");
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (-1);
	data.time = 0;
	init_window(&data);
	init_map(&data, argv[1]);
	print_map(&data);
	if (!data.map)
		return (-1);
	init_view(&data);
	init_mouse(&data);
	keyboard_init(&data);
	fdf_hooks(&data);
}
