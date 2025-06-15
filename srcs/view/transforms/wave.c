/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:27:25 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 20:11:41 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

void init_wave(t_data *data)
{
	t_wave *wave;

	wave = &data->view.wave;
	wave->enabled_x = false;
	wave->enabled_y = false;
	wave->amplitude = 1;
	wave->k = 0.8;
	wave->angular_freq = 1.0 + 
			((data->map->map_width + data->map->map_height) / 2 ) / 100.0;
	wave->propagation_speed = wave->angular_freq * 2.0;
}

double apply_wave(t_data *data, t_point *point)
{
	t_wave *wave;

	wave = &data->view.wave;
	if (!wave->enabled_x && !wave->enabled_y)
		return (0.0);
	if (wave->propagation_speed < 2.0)
		wave->propagation_speed = 2.0;
	if (wave->enabled_x)
		wave->distance = point->x;
	else
		wave->distance = point->y;
	if (wave->distance > wave->propagation_speed * data->time)
		return (0.0);
	return (wave->amplitude 
		* sin((wave->k * wave->distance) - (wave->angular_freq * data->time)));
}