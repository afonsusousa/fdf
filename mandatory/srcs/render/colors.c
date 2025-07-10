/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:56:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 23:21:25 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define EXTRACT_R(color) ((color >> 16) & 0xFF)
#define EXTRACT_G(color) ((color >> 8) & 0xFF)
#define EXTRACT_B(color) (color & 0xFF)
#define PACK_RGB(r, g, b) ((r << 16) | (g << 8) | b)

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
		r = (int)(140 + (255 - 140) * (ratio - 0.5f) * 2.0f);
		g = (int)(120 + (140 - 120) * (ratio - 0.5f) * 2.0f);
		b = (int)(180 + (120 - 180) * (ratio - 0.5f) * 2.0f);
	}
	return ((r << 16) | (g << 8) | b);
}

int	interpolate_color(int color1, int color2, float t)
{
    return (PACK_RGB(
        EXTRACT_R(color1) + (int)((EXTRACT_R(color2) - EXTRACT_R(color1)) * t),
        EXTRACT_G(color1) + (int)((EXTRACT_G(color2) - EXTRACT_G(color1)) * t),
        EXTRACT_B(color1) + (int)((EXTRACT_B(color2) - EXTRACT_B(color1)) * t)
    ));
}

void	colorize_points(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map->points_count)
	{
		if (!data->map->points[i].colored)
			data->map->points[i].color = get_color_from_z(data,
					&data->map->points[i]);
		i++;
	}
}
