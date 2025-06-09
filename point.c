/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:56:24 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 19:14:32 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void rotate_x_coords(double coords[3], double alpha)
{
	double cos_a;
	double sin_a;
	double temp_y;
	double temp_z;
	
	cos_a = cos(alpha);
	sin_a = sin(alpha);
	temp_y = coords[1];
	temp_z = coords[2];
	coords[1] = temp_y * cos_a - temp_z * sin_a;
	coords[2] = temp_y * sin_a + temp_z * cos_a;
}

void rotate_y_coords(double coords[3], double beta)
{
	double cos_b;
	double sin_b;
	double temp_x;
	double temp_z;
	
	cos_b = cos(beta);
	sin_b = sin(beta);
	temp_x = coords[0];
	temp_z = coords[2];
	coords[0] = temp_x * cos_b + temp_z * sin_b;
	coords[2] = -temp_x * sin_b + temp_z * cos_b;
}

void rotate_z_coords(double coords[3], double gamma)
{
	double cos_g;
	double sin_g;
	double temp_x;
	double temp_y;
	
	cos_g = cos(gamma);
	sin_g = sin(gamma);
	temp_x = coords[0];
	temp_y = coords[1];
	coords[0] = temp_x * cos_g - temp_y * sin_g;
	coords[1] = temp_x * sin_g + temp_y * cos_g;
}

void center_coordinates(t_data *data)
{
	int center_x;
	int center_y;
	int i;
	
	center_x = data->map->map_width / 2;
	center_y = data->map->map_height / 2;
	for (i = 0; i < data->map->points_count; i++)
	{
		data->map->points[i].x -= center_x;
		data->map->points[i].y -= center_y;
	}
}

void rotate_point(t_point *source, t_rotation *rotation)
{
	double coords[3];

	coords[0] = (double)source->x;
	coords[1] = (double)source->y;
	coords[2] = (double)source->z * rotation->scale;
	rotate_x_coords(coords, rotation->alpha);
	rotate_y_coords(coords, rotation->beta);
	rotate_z_coords(coords, rotation->gamma);
	coords[0] *= rotation->zoom;
	coords[1] *= rotation->zoom;
	coords[2] *= rotation->zoom;
	
	// Store the transformed 3D coordinates
	source->world_3d[0] = coords[0];
	source->world_3d[1] = coords[1];
	source->world_3d[2] = coords[2];
	
	source->display[0] = (int)((coords[0] - coords[1]) * cos(rotation->angle));
	source->display[1] = (int)((coords[0] + coords[1]) * sin(rotation->angle) - coords[2]);
}