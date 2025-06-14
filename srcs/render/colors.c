/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:56:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:40:38 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

int get_color_from_z(int z_value, int min_z, int max_z)
{
	float ratio;
	int r;
	int g;
	int b;
	
	if (max_z == min_z)
		ratio = 0.5f;
	else
		ratio = (float)(z_value - min_z) / (float)(max_z - min_z);
	if (ratio <= 0.5f)
	{
		float t = ratio * 2.0f;
		r = (int)(80 + (140 - 80) * t);    // 80 → 140 (warm purple to lavender)
		g = (int)(70 + (120 - 70) * t);    // 70 → 120 (gentle purple-blue)
		b = (int)(200 + (180 - 200) * t);  // 200 → 180 (bright blue to lavender)
	}
	else
	{
		float t = (ratio - 0.5f) * 2.0f;
		r = (int)(140 + (255 - 140) * t);  // 140 → 255 (lavender to salmon)
		g = (int)(120 + (140 - 120) * t);  // 120 → 140 (lavender to salmon)
		b = (int)(180 + (120 - 180) * t);  // 180 → 120 (lavender to salmon)
	}
	return (r << 16) | (g << 8) | b;
}

int interpolate_color(int color1, int color2, float t)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;
	
	int r = (int)(r1 + (r2 - r1) * t);
	int g = (int)(g1 + (g2 - g1) * t);
	int b = (int)(b1 + (b2 - b1) * t);
	
	return (r << 16) | (g << 8) | b;
}

// void set_line_color(t_line *line, t_data *data)
// {
// 	line->color1 = get_color_from_z(line->z1 * data->view.scale,
// 				data->map->min_z * data->view.scale,
// 				data->map->max_z * data->view.scale);
// 	line->color2 = get_color_from_z(line->z2 * data->view.scale, 
// 				data->map->min_z * data->view.scale,
// 				data->map->max_z * data->view.scale);
// }

