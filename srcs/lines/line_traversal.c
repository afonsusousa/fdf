/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_traversal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:07:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 16:36:30 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void draw_lines_traversal(t_data *data)
{
	int x, y;
	
	if (data->view.alpha > M_PI)
		y = data->map->map_height - 1;
	else
		y = 0;
	while (y < data->map->map_height && y >= 0)
	{
		if (data->view.beta > M_PI)
			x = data->map->map_width - 1;
		else
			x = 0;
		while (x < data->map->map_width && x >= 0)
		{
			if (x != data->map->map_width - 1)
				draw_line_with_offset(data, get_point(data, x, y), 
					get_point(data, x + 1, y));
			if (y != data->map->map_height - 1)
				draw_line_with_offset(data, get_point(data, x, y), 
					get_point(data, x, y + 1));
			x += -2 * (data->view.beta > M_PI) + 1;
		}
		y += -2 * (data->view.alpha > M_PI) + 1;
	}
}
