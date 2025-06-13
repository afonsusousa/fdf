/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ripple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:26:55 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 01:53:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

double distance_from(t_point *center, t_point *point)
{
	int x_delta;
	int y_delta;
	double distance;

	x_delta = point->x - center->x;
	y_delta = point->y - center->y;
	distance = sqrt((x_delta * x_delta) + (y_delta * y_delta));
	return (distance);
}
double ripple_height(t_data *data, t_point *point)
{
	int amplitude;
	t_point *center;
	double k;
	double angular_freq;


	center = get_point(data, (data->map->map_width / 2), (data->map->map_height / 3));
	k = 1;
	angular_freq = 1;
	amplitude = 1;
	return (amplitude * sin((k * distance_from(center, point) - (angular_freq * data->time))));
}