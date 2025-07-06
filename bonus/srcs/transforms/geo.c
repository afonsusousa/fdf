/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:23:40 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/06 22:27:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#ifdef AUDIO

void	spherize(t_point *point, t_data *data)
{
	float	radius;

	if (data->view.view_mode != SPHERICAL)
		return ;
	radius = data->map->radius + (point->z * point->scale);
	point->world_3d[0] = radius * cos(point->globe_2d[0])
		* cos(point->globe_2d[1]);
	point->world_3d[1] = radius * cos(point->globe_2d[0])
		* sin(point->globe_2d[1]);
	point->world_3d[2] = radius * sin(point->globe_2d[0]);
}

#else

void	spherize(t_point *point, t_data *data)
{
	float	radius;

	if (data->view.view_mode != SPHERICAL)
		return ;
	radius = data->map->radius + (point->z * data->view.scale);
	point->world_3d[0] = radius * cos(point->globe_2d[0])
		* cos(point->globe_2d[1]);
	point->world_3d[1] = radius * cos(point->globe_2d[0])
		* sin(point->globe_2d[1]);
	point->world_3d[2] = radius * sin(point->globe_2d[0]);
}

#endif

void	polarize_points(t_map *map)
{
	int		i;
	float	steps_x;
	float	steps_y;

	steps_x = (M_PI * 2) / (float)map->map_width;
	steps_y = M_PI / (float)map->map_height;
	map->radius = fmax(map->map_width, map->map_height) / 3.0;
	i = 0;
	while (i < map->points_count)
	{
		map->points[i].globe_2d[1] = (map->points[i].x - map->map_width / 2.0)
			* steps_x;
		map->points[i].globe_2d[0] = (map->points[i].y - map->map_height / 2.0)
			* steps_y;
		i++;
	}
}
