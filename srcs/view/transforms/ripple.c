/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:26:55 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 18:59:50 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include <math.h> // Ensure math.h is included for sqrt and sin

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

double ripple_height(t_data *data, t_point *point)
{
    int amplitude;
    double k;
    double angular_freq;
    double dist_to_center;
    double propagation_speed;

    k = 0.8;
    angular_freq = 1.0 + (data->map->map_size / 100.0);
    amplitude = 1;
    propagation_speed = angular_freq * 2.0;
    if (propagation_speed < 2.0)
        propagation_speed = 2.0;
    dist_to_center = distance_from_center(data, point);
    if (dist_to_center > propagation_speed * data->time)
        return (0.0);
    return ((double)amplitude 
        * sin((k * dist_to_center) - (angular_freq * data->time)));
}