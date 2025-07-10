/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:29:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 00:28:57 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#ifdef AUDIO

void	transform_point(t_data *data, t_point *point)
{
	set_point_audio_scale(data, point);
	point->world_3d[0] = (double)point->x;
	point->world_3d[1] = (double)point->y;
	point->world_3d[2] = (double)point->z * point->scale;
	spherize(point, data);
	cylindrize(point, data);
	bend(data, point);
	rotate_x_coords(point->world_3d, data->view.alpha);
	rotate_y_coords(point->world_3d, data->view.beta);
	rotate_z_coords(point->world_3d, data->view.gamma);
	ripple(data, point);
	wave(data, point);
	point->world_3d[0] *= data->view.zoom;
	point->world_3d[1] *= data->view.zoom;
	point->world_3d[2] *= data->view.zoom;
	project(data, point);
}

#else

void	transform_point(t_data *data, t_point *point)
{
	point->world_3d[0] = (double)point->x;
	point->world_3d[1] = (double)point->y;
	point->world_3d[2] = (double)point->z * data->view.scale;
	spherize(point, data);
	cylindrize(point, data);
	bend(data, point);
	rotate_x_coords(point->world_3d, data->view.alpha);
	rotate_y_coords(point->world_3d, data->view.beta);
	rotate_z_coords(point->world_3d, data->view.gamma);
	ripple(data, point);
	wave(data, point);
	point->world_3d[0] *= data->view.zoom;
	point->world_3d[1] *= data->view.zoom;
	point->world_3d[2] *= data->view.zoom;
	project(data, point);
}

#endif

void	transform(t_data *data)
{
	int					i;
	static const double	iso_view[3] = {0.577, 0.577, 0.577};
	double				dot_product;
	t_point				*points;
	int					count;

	points = data->map->points;
	count = data->map->points_count;
	i = -1;
	while (++i < count)
		transform_point(data, &points[i]);
	dot_product = data->view.axis[0] * iso_view[0] + data->view.axis[1]
		* iso_view[1] + data->view.axis[2] * iso_view[2];
	data->view.top_down = !(dot_product > 0.15);
}
