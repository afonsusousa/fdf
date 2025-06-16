/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:28:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 18:42:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	init_view(t_data *data)
{
	data->view.alpha = 0;
	data->view.beta = 0;
	data->view.gamma = 0;
	data->view.axis[0] = 0.0;
	data->view.axis[1] = 0.0;
	data->view.axis[2] = 1.0;
	data->view.zoom = 15;
	data->view.angle = 0.523599;
	data->view.rotation_step = 0.01;
	data->view.zoom_step = 1;
	data->view.scale_step = 0.005;
	data->view.shift_step = 2;
	data->view.render_mode = RENDER_PRIORITY;
	data->view.view_mode = ISOMETRIC;
	data->view.auto_rotate = 0;
	data->view.offset_x = (data->window_width + data->menu_width) / 2;
	data->view.offset_y = data->window_height / 2;
	init_ripple(data);
	init_wave(data);
	init_optimal_scale(data);
	if (data->view.scale < 0.02)
		data->view.scale = 0.02;
}

void	init_optimal_scale(t_data *data)
{
	int		z_range;
	int		map_size;
	double	base_scale;
	double	z_factor;

	z_range = data->map->max_z - data->map->min_z;
	map_size = (data->map->map_width + data->map->map_height) / 2;
	if (map_size > 100)
		base_scale = 0.08;
	else if (map_size > 50)
		base_scale = 0.15;
	else if (map_size > 20)
		base_scale = 0.25;
	else
		base_scale = 0.4;
	if (z_range == 0)
		z_factor = 0.5;
	else if (z_range <= 5)
		z_factor = 0.4 + (z_range * 0.1);
	else if (z_range <= 50)
		z_factor = 0.9 - ((z_range - 5) * 0.008);
	else
		z_factor = 0.54 - ((z_range - 50) * 0.003);
	data->view.scale = base_scale * z_factor;
}
