/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:26:55 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 20:29:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include <math.h> // Ensure math.h is included for sqrt and sin

void init_ripple(t_data *data)
{
	t_ripple *ripple;

	ripple = &data->view.ripple;
	ripple->enabled = false;
	ripple->amplitude = 1;
	ripple->k = 0.8;
	ripple->angular_freq = 1.0 + 
			((data->map->map_width + data->map->map_height) / 2 ) / 100.0;
	ripple->propagation_speed = ripple->angular_freq * 2.0;
	ripple->distance = 0.0;
}

static double distance_from_center(t_data *data, t_point *point)
{
    int x_delta;
    int y_delta;
    double distance;

    x_delta = point->x - data->map->center->x;
    y_delta = point->y - data->map->center->y;
    distance = sqrt((double)(x_delta * x_delta) + (double)(y_delta * y_delta));
    return (distance);
}

double apply_ripple(t_data *data, t_point *point)
{
	t_ripple *ripple;

	ripple = &data->view.ripple;
	if (!ripple->enabled)
		return (0.0);
    if (ripple->propagation_speed < 2.0)
        ripple->propagation_speed = 2.0;
    ripple->distance = distance_from_center(data, point);
    if (ripple->distance > ripple->propagation_speed * data->time)
        return (0.0);
    return ((double)ripple->amplitude 
        * cos((ripple->k * ripple->distance) 
		- (ripple->angular_freq * data->time)));
}