/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:56:24 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 00:23:55 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

void init_point(t_point *point, int x, int y, char *value)
{
	point->x = x;
	point->y = y;
	point->z = ft_atoi(value);
	point->display[0] = 0;
	point->display[1] = 0;
	point->display[2] = 0;  // Initialize screen-space Z coordinate
	point->world_3d[0] = (double)x;
	point->world_3d[1] = (double)y;
	point->world_3d[2] = (double)point->z;
}

void center_coordinates(t_data *data)
{
	int center_x;
	int center_y;
	int i;
	
	center_x = data->map->map_width / 2;
	center_y = data->map->map_height / 2;
	i = 0;
	while (i < data->map->points_count)
	{
		data->map->points[i].x -= center_x;
		data->map->points[i].y -= center_y;
		i++;
	}
}