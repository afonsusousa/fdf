/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:27:25 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 20:21:03 by amagno-r         ###   ########.fr       */
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
	wave->angular_freq_x = 1.0 + (data->map->map_width / 100.0);
	wave->angular_freq_y = 1.0 + (data->map->map_height / 100.0);
	wave->propagation_speed_x = wave->angular_freq_x * 2.0;
	wave->propagation_speed_y = wave->angular_freq_y * 2.0;
}

double apply_wave(t_data *data, t_point *point)
{
	t_wave *wave;

	wave = &data->view.wave;
	if (!wave->enabled_x && !wave->enabled_y)
		return (0.0);
	
	if (wave->enabled_x)
	{
		wave->distance = abs(point->y);
		if (wave->distance > wave->propagation_speed_x * data->time)
			return (0.0);
		return (wave->amplitude 
			* sin((wave->k * wave->distance) - (wave->angular_freq_x * data->time)));
	}
	else if (wave->enabled_y)
	{
		wave->distance = abs(point->x);
		if (wave->distance > wave->propagation_speed_y * data->time)
			return (0.0);
		return (wave->amplitude 
			* sin((wave->k * wave->distance) - (wave->angular_freq_y * data->time)));
	}
	return (0.0);
}