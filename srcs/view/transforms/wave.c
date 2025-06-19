/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:27:25 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 01:20:05 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

void	init_wave(t_data *data)
{
	t_wave	*wave;

	wave = &data->view.wave;
	wave->enabled_x = false;
	wave->enabled_y = false;
	wave->amplitude = 1;
	wave->k = 0.8;
	wave->angular_freq_x = 1.0 + (data->map->map_width / 50.0);
	wave->angular_freq_y = 1.0 + (data->map->map_height / 50.0);
	wave->propagation_speed_x = wave->angular_freq_x / wave->k;
	wave->propagation_speed_y = wave->angular_freq_y / wave->k;
}

static void	apply_wave_x(t_data *data, t_point *point)
{
	t_wave	*wave;

	wave = &data->view.wave;
	if (!wave->enabled_x)
		return ;
	wave->distance = point->y + (data->map->map_height / 2);
	if (wave->distance > wave->propagation_speed_x * wave->x_time)
		return ;
	point->world_3d[2] += (double )((wave->amplitude 
			* sin((wave->k * wave->distance)
			- (wave->angular_freq_x * wave->x_time))));
}

static void	apply_wave_y(t_data *data, t_point *point)
{
	t_wave	*wave;

	wave = &data->view.wave;
	if (!wave->enabled_y)
		return ;
	wave->distance = point->x + (data->map->map_width / 2);
	if (wave->distance > wave->propagation_speed_y * wave->y_time)
		return ;
	point->world_3d[2] += (double )(wave->amplitude 
			* sin((wave->k * wave->distance)
			- (wave->angular_freq_y * wave->y_time)));
}

void	wave(t_data *data, t_point *point)
{
	if (!data->view.wave.enabled_x && !data->view.wave.enabled_y)
		return ;
	apply_wave_x(data, point);
	apply_wave_y(data, point);
}
