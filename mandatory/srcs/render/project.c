/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:29:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/06 22:13:03 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project(t_data *data, t_point *point)
{
	point->display[0] = (int)((point->world_3d[0] - point->world_3d[1])
			* cos(data->view.angle));
	point->display[1] = (int)((point->world_3d[0] + point->world_3d[1])
			* sin(data->view.angle) - point->world_3d[2]);
}

void	transform_point(t_data *data, t_point *point)
{
	point->world_3d[0] = (double)point->x;
	point->world_3d[1] = (double)point->y;
	point->world_3d[2] = (double)point->z * data->view.scale;
	rotate_x_coords(point->world_3d, data->view.alpha);
	rotate_y_coords(point->world_3d, data->view.beta);
	rotate_z_coords(point->world_3d, data->view.gamma);
	point->world_3d[0] *= data->view.zoom;
	point->world_3d[1] *= data->view.zoom;
	point->world_3d[2] *= data->view.zoom;
	project(data, point);
}

void	transform(t_data *data)
{
	int					i;

	i = -1;
	while (++i < data->map->points_count)
		transform_point(data, &data->map->points[i]);
}
