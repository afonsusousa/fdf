/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripple_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:26:55 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 23:08:35 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_ripple(t_data *data)
{
	t_ripple	*ripple;

	ripple = &data->view.ripple;
	ripple->time = 0.0;
	ripple->enabled = false;
	ripple->amplitude = 1;
	ripple->k = 0.8;
	ripple->angular_freq = 1.0 + ((data->map->map_width + data->map->map_height)
			/ 2) / 100.0;
	ripple->propagation_speed = ripple->angular_freq / ripple->k;
	ripple->distance = 0.0;
}

static double	distance_from_center(t_data *data, t_point *point)
{
	int		x_delta;
	int		y_delta;
	double	distance;

	if (data->view.view_mode != SPHERICAL)
	{
		x_delta = point->x - data->map->center->x;
		y_delta = point->y - data->map->center->y;
	}
	else
	{
		x_delta = point->axial[0] * data->map->radius;
		y_delta = point->axial[1] * data->map->radius;
	}
	distance = sqrt((double)(x_delta * x_delta) + (double)(y_delta * y_delta));
	return (distance);
}

void	ripple(t_data *data, t_point *point)
{
	t_ripple	*ripple;

	ripple = &data->view.ripple;
	if (!ripple->enabled)
		return ;
	if (ripple->propagation_speed < 2.0)
		ripple->propagation_speed = 2.0;
	ripple->distance = distance_from_center(data, point);
	if (ripple->distance > ripple->propagation_speed * ripple->time)
		return ;
	point->world_3d[2] += (double)(ripple->amplitude * cos((ripple->k
					* ripple->distance) - (ripple->angular_freq
					* ripple->time)));
}
