/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:29:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 16:43:59 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotate_point(t_point *source, t_view *view)
{
	double coords[3];

	coords[0] = (double)source->x;
	coords[1] = (double)source->y;
	coords[2] = (double)source->z * view->scale;
	rotate_x_coords(coords, view->alpha);
	rotate_y_coords(coords, view->beta);
	rotate_z_coords(coords, view->gamma);
	coords[0] *= view->zoom;
	coords[1] *= view->zoom;
	coords[2] *= view->zoom;
	
	// Store the transformed 3D coordinates
	source->world_3d[0] = coords[0];
	source->world_3d[1] = coords[1];
	source->world_3d[2] = coords[2];
	
	source->display[0] = (int)((coords[0] - coords[1]) * cos(view->angle));
	source->display[1] = (int)((coords[0] + coords[1]) * sin(view->angle) - coords[2]);
}

void rotate_vector(double vector[3], t_view *view)
{
    rotate_x_coords(vector, view->alpha);
    rotate_y_coords(vector, view->beta);
    rotate_z_coords(vector, view->gamma);
}

void rotate(t_data *data)
{
	for (int i = 0; i < data->map->points_count; i++)
		rotate_point(&data->map->points[i], &data->view);
	double up_vector[3] = {0.0, 0.0, 1.0};
    rotate_vector(up_vector, &data->view);
    double iso_view[3] = {0.577, 0.577, 0.577};
    double dot_product = up_vector[0] * iso_view[0] + 
                        up_vector[1] * iso_view[1] + 
                        up_vector[2] * iso_view[2];
    if (dot_product > 0.1)  // Threshold for significant alignment
    {
		data->view.top_down = true;
        return ;
    }
	data->view.top_down = false;
}