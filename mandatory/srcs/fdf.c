/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:42:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/06 22:08:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

void	fdf_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, rotate_and_render, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx_win, 17, 1L << 17, handle_close_button, data);
	mlx_loop(data->mlx);
}

void	init_window(t_data *data)
{
	data->w_height = 1080;
	data->w_width = 1920;
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

	if (argc == 1)
	{
		ft_printf("No file specified.\n");
		return (-1);
	}
	else if (argc != 2)
		ft_printf("Too many files specified... Opening first...\n");
	ft_memset(&data, 0, sizeof(t_data));
	init_map(&data, argv[1]);
	if (!data.map)
		return (-1);
	print_map(&data);
	init_window(&data);
	init_view(&data);
	keyboard_init(&data);
	fdf_hooks(&data);
}