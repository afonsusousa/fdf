/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:56:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 17:55:01 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_color	get_color_from_z(t_data *data, t_point *point)
{
	float	ratio;
	t_color	result;

	if (data->map->max_z == data->map->min_z)
		ratio = 0.5f;
	else
		ratio = (float)(point->z - data->map->min_z) / (float)(data->map->max_z
				- data->map->min_z);
	if (ratio <= 0.5f)
	{
		result.s_rgba.r = (int)(80 + (140 - 80) * ratio * 2.0f);
		result.s_rgba.g = (int)(70 + (120 - 70) * ratio * 2.0f);
		result.s_rgba.b = (int)(200 + (180 - 200) * ratio * 2.0f);
	}
	else
	{
		result.s_rgba.r = (int)(140 + (255 - 140) * (ratio - 0.5f) * 2.0f);
		result.s_rgba.g = (int)(120 + (140 - 120) * (ratio - 0.5f) * 2.0f);
		result.s_rgba.b = (int)(180 + (120 - 180) * (ratio - 0.5f) * 2.0f);
	}
	result.s_rgba.a = 0;
	return (result);
}

int	interpolate_color(t_color c1, t_color c2, unsigned char t)
{
	t_color	result;

	if (t == 255)
		return (c2.hex);
	if (t == 0)
		return (c1.hex);
	result.s_rgba.r = c1.s_rgba.r + (((c2.s_rgba.r - c1.s_rgba.r) * t) >> 8);
	result.s_rgba.g = c1.s_rgba.g + (((c2.s_rgba.g - c1.s_rgba.g) * t) >> 8);
	result.s_rgba.b = c1.s_rgba.b + (((c2.s_rgba.b - c1.s_rgba.b) * t) >> 8);
	result.s_rgba.a = 0;
	return (result.hex);
}

void	colorize_points(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->map->points_count)
	{
		if (!data->map->points[i].colored)
			data->map->points[i].color = get_color_from_z(data,
					&data->map->points[i]);
		i++;
	}
}
