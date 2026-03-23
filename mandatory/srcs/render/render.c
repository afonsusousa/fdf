/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:33:08 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/06 22:12:41 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_image(t_data *data)
{
	int	background_color;

	(void)data;
	background_color = 0x1a1a2e;
	draw_background(data, background_color);
}

int	rotate_and_render(t_data *data)
{
	clear_image(data);
	transform(data);
	draw_lines_priority(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}
