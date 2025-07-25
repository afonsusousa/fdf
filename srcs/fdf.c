/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 23:09:16 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

void	fdf_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, rotate_and_render, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->mlx_win, 17, 1L << 17, handle_close_button, data);
	mlx_mouse_hook(data->mlx_win, handle_mouse_scroll, data);
	mlx_hook(data->mlx_win, 4, 1L << 2, handle_mouse_press, data);
	mlx_hook(data->mlx_win, 5, 1L << 3, handle_mouse_release, data);
	mlx_hook(data->mlx_win, 6, 1L << 6, handle_mouse_move, data);
	mlx_loop(data->mlx);
}

void	init_window(t_data *data)
{
	data->w_height = 1080;
	data->w_width = 1920;
	data->m_ratio = 6;
	data->m_width = data->w_width / data->m_ratio;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->mlx_win = mlx_new_window(data->mlx, data->w_width,
			data->w_height, "amagno-r - FDF");
	if (!data->mlx_win)
		free_data(data);
	data->img = mlx_new_image(data->mlx, data->w_width,
			data->w_height);
	if (!data->img)
		free_data(data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (-1);
	ft_memset(&data, 0, sizeof(t_data));
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
