/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:56:24 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 18:04:02 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_point(t_point *point, int x, int y, char *value)
{
	point->paint = false;
	point->x = x;
	point->y = y;
	point_atoi(point, value);
	point->display[0] = 0;
	point->display[1] = 0;
	point->world_3d[0] = (double)x;
	point->world_3d[1] = (double)y;
	point->world_3d[2] = (double)point->z;
}

void	center_coordinates(t_data *data)
{
	int	center_x;
	int	center_y;
	int	i;

	center_x = data->map->map_width / 2;
	center_y = data->map->map_height / 2;
	data->map->center = get_point(data, center_x, center_y);
	i = 0;
	while (i < data->map->points_count)
	{
		data->map->points[i].x -= center_x;
		data->map->points[i].y -= center_y;
		i++;
	}
}

bool	in_screen(t_data *data, t_point *point)
{
	return (data->map->points_count < 10000 || (((point->display[0]
					+ data->view.off_x) > (data->m_width - data->view.zoom))
			&& (point->display[0] + data->view.off_x) < (data->w_width
				+ data->view.zoom) && (point->display[1]
				+ data->view.off_y) > (-data->view.zoom) && (point->display[1]
				+ data->view.off_y) < (data->w_height + data->view.zoom)));
}
