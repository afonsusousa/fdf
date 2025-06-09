/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:29:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 00:09:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void rotate_vector(double vector[3], t_rotation *rotation)
{
    rotate_x_coords(vector, rotation->alpha);
    rotate_y_coords(vector, rotation->beta);
    rotate_z_coords(vector, rotation->gamma);
}

void rotate(t_data *data)
{
	for (int i = 0; i < data->map->points_count; i++)
		rotate_point(&data->map->points[i], &data->rotation);
	double up_vector[3] = {0.0, 0.0, 1.0};
    rotate_vector(up_vector, &data->rotation);
    double iso_view[3] = {0.577, 0.577, 0.577};
    double dot_product = up_vector[0] * iso_view[0] + 
                        up_vector[1] * iso_view[1] + 
                        up_vector[2] * iso_view[2];
    if (dot_product > 0.33)  // Threshold for significant alignment
    {
		data->rotation.top_down = true;
        return ;
    }
	data->rotation.top_down = false;
}