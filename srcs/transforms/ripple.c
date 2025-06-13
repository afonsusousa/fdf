/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:26:55 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 17:10:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <math.h> // Ensure math.h is included for sqrt and sin

static double distance_from(t_point *center, t_point *point)
{
    int x_delta;
    int y_delta;
    double distance;

    // Assuming point->x and center->x are original map grid coordinates
    x_delta = point->x - center->x;
    y_delta = point->y - center->y;
    distance = sqrt((double)(x_delta * x_delta) + (double)(y_delta * y_delta)); // Cast to double before sqrt
    return (distance);
}

double ripple_height(t_data *data, t_point *point)
{
    int amplitude;
    t_point *center;
    double k;
    double angular_freq;
    double dist_to_center;

    center = get_point(data, 
            (data->map->map_width / 2),
            (data->map->map_height / 2));
    k = 0.8;
    angular_freq = 1.5; 
    amplitude = 1;      
    dist_to_center = distance_from(center, point);
    if (dist_to_center > amplitude * data->time)
        return (0.0);
    // double ring_thickness = 15.0; // example thickness
    // if (dist_to_center < max_ripple_reach - ring_thickness && max_ripple_reach > ring_thickness)
    // {
    //     return (0.0);
    // }
    return ((double)amplitude 
        * sin((k * dist_to_center) - (angular_freq * data->time)));
}