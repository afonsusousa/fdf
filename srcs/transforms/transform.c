/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:29:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 03:51:59 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void x_transforms(t_data *data, t_point *point, double coords[3])
{
	(void) point;
	rotate_x_coords(coords, data->view.alpha);
}

void y_transforms(t_data *data, t_point *point, double coords[3])
{
	(void) point;
	rotate_y_coords(coords, data->view.beta);
}

void z_transforms(t_data *data, t_point *point, double coords[3])
{
	if (data->view.ripple)
		coords[2] += ripple_height(data, point);
	if (data->view.wave_x || data->view.wave_y)
		coords[2] += wave_height(data, point);
	rotate_z_coords(coords, data->view.gamma);
}
void transform_point(t_data *data, t_point *point)
{
	double coords[3];

	coords[0] = (double)point->x;
	coords[1] = (double)point->y;
	coords[2] = (double)point->z * data->view.scale;
	
	x_transforms(data, point, coords);
	y_transforms(data, point, coords);
	z_transforms(data, point, coords);

	coords[0] *= data->view.zoom;
	coords[1] *= data->view.zoom;
	coords[2] *= data->view.zoom;

	point->world_3d[0] = coords[0];
	point->world_3d[1] = coords[1];
	point->world_3d[2] = coords[2];
	
	point->display[0] = (int)((coords[0] - coords[1]) * cos(data->view.angle));
	point->display[1] = (int)((coords[0] + coords[1]) * sin(data->view.angle) - coords[2]);
}

void transform(t_data *data)
{
	int i;
	double iso_view[3] = {0.577, 0.577, 0.577};
	double dot_product;
	i = 0;
	while (i < data->map->points_count)
	{
		transform_point(data, &data->map->points[i]);
		i++;
	}
	dot_product = data->view.axis[0] * iso_view[0] +
				  data->view.axis[1] * iso_view[1] +
				  data->view.axis[2] * iso_view[2];
	data->view.top_down = !(dot_product > 0.15);
	dot_product = data->view.axis[0] * iso_view[0] +
				  data->view.axis[1] * iso_view[1];
	data->view.left_tilt = !(dot_product > 0.15);
	dot_product = 0 +
				  data->view.axis[1] * iso_view[1] +
				  data->view.axis[2] * iso_view[2];
	data->view.right_tilt = !(dot_product > 0.15);
}