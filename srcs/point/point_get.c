/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:26:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 20:16:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*get_point(t_data *data, int x, int y)
{
	if (!data || !data->map || !data->map->points)
		return (NULL);
	if (x < 0 || y < 0 || x >= data->map->map_width || y >= data->map->map_height)
		return (NULL);
	
	return &data->map->points[y * data->map->map_width + x];
}