/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:07:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/11 03:13:34 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <math.h>

void draw_lines_traversal(t_data *data)
{
	int x, y;
	int x_dir, y_dir;

	if (data->view.gamma > M_PI)
	{
		x_dir = -2 * (data->view.alpha > M_PI) + 1;
		y_dir = -2 * (data->view.beta > M_PI) + 1;
		y = (data->view.beta > M_PI) ? data->map->map_height - 1 : 0;
	}
	else
	{
		x_dir = -2 * (data->view.beta > M_PI) + 1;
		y_dir = -2 * (data->view.alpha > M_PI) + 1;
		y = (data->view.alpha > M_PI) ? data->map->map_height - 1 : 0;
	}
	while (y < data->map->map_height && y >= 0)
	{
		if (x_dir > 0)
			x = 0;
		else
			x = data->map->map_width - 1;
		while (x < data->map->map_width && x >= 0)
		{
			if (x != data->map->map_width - 1)
				draw_line_with_offset(data, get_point(data, x, y),
									  get_point(data, x + 1, y));
			if (y != data->map->map_height - 1)
				draw_line_with_offset(data, get_point(data, x, y),
									  get_point(data, x, y + 1));
			x += x_dir;
		}
		y += y_dir;
	}
}
