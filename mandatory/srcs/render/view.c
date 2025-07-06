/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:28:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/06 21:46:24 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_view(t_data *data)
{
	data->view.alpha = 0;
	data->view.beta = 0;
	data->view.gamma = 0;
	data->view.zoom = 25;
	data->view.angle = 0.523599;
	data->view.off_x = data->w_width / 2;
	data->view.off_y = data->w_height / 2;
	init_optimal_scale(data);
}

void	init_optimal_scale(t_data *data)
{
	int		max_z;
	double	scale;

	max_z = abs(data->map->max_z);
	if (abs(data->map->min_z) > max_z)
		max_z = abs(data->map->min_z);
	if (max_z == 0)
		scale = 0.8;
	else if (max_z <= 5)
		scale = 0.6;
	else if (max_z <= 10)
		scale = 0.4;
	else if (max_z <= 25)
		scale = 0.3;
	else if (max_z <= 50)
		scale = 0.2;
	else if (max_z <= 100)
		scale = 0.12;
	else
		scale = 0.06;
	data->view.scale = scale;
}
