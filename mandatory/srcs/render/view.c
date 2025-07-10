/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:28:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 20:17:43 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_view(t_data *data)
{
	int	i;

	i = -1;
	data->view.alpha = 0;
	data->view.beta = 0;
	data->view.gamma = 0;
	data->view.zoom = 25;
	data->view.scale = 1;
	data->view.angle = 0.523599;
	data->view.off_x = data->w_width / 2;
	data->view.off_y = data->w_height / 2;
	while (data->view.zoom > 2)
	{
		transform(data);
		i = -1;
		while (++i < data->map->points_count)
			if (!in_screen(data, &data->map->points[i]))
				break ;
		if (i == data->map->points_count)
			break ;
		data->view.zoom--;
	}
	init_optimal_scale(data);
}

void	init_optimal_scale(t_data *data)
{
	int		i;
	while (data->view.scale > 0.01)
	{
		transform(data);
		i = -1;
		while (++i < data->map->points_count)
			if (!in_screen(data, &data->map->points[i]))
				break ;
		if (i == data->map->points_count)
			break ;
		data->view.scale -= 0.01;
	}
}
