/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:56:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 02:56:01 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

int	get_color_from_z(t_data *data, t_point *point)
{
	float	ratio;
	int		r;
	int		g;
	int		b;

	if (data->map->max_z == data->map->min_z)
		ratio = 0.5f;
	else
		ratio = (float)(point->z - data->map->min_z) / (float)(data->map->max_z
				- data->map->min_z);
	if (ratio <= 0.5f)
	{
		r = (int)(80 + (140 - 80) * ratio * 2.0f);
		g = (int)(70 + (120 - 70) * ratio * 2.0f);
		b = (int)(200 + (180 - 200) * ratio * 2.0f);
	}
	else
	{
		r = (int)(140 + (255 - 140) * ratio * 2.0f);
		g = (int)(120 + (140 - 120) * ratio * 2.0f);
		b = (int)(180 + (120 - 180) * ratio * 2.0f);
	}
	return ((r << 16) | (g << 8) | b);
}

int	interpolate_color(int color1, int color2, float t)
{
	int	rgb1[3];
	int	rgb2[3];
	int	result[3];

	rgb1[0] = (color1 >> 16) & 0xFF;
	rgb1[1] = (color1 >> 8) & 0xFF;
	rgb1[2] = color1 & 0xFF;
	rgb2[0] = (color2 >> 16) & 0xFF;
	rgb2[1] = (color2 >> 8) & 0xFF;
	rgb2[2] = color2 & 0xFF;
	result[0] = (int)(rgb1[0] + (rgb2[0] - rgb1[0]) * t);
	result[1] = (int)(rgb1[1] + (rgb2[1] - rgb1[1]) * t);
	result[2] = (int)(rgb1[2] + (rgb2[2] - rgb1[2]) * t);
	return ((result[0] << 16) | (result[1] << 8) | result[2]);
}

void	colorize_points(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map->points_count)
	{
		if (!data->map->points[i].paint)
			data->map->points[i].color = get_color_from_z(data,
					&data->map->points[i]);
		i++;
	}
}
