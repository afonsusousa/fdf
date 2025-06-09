/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:56:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 02:53:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int get_color_from_z(int z_value, int min_z, int max_z)
{
	float ratio;
	int r, g, b;
	
	// Dracula color palette
	// Low: Purple (#BD93F9)
	// Mid: Pink (#FF79C6) 
	// High: Cyan (#8BE9FD)
	
	if (max_z == min_z)
		ratio = 0.5f;
	else
		ratio = (float)(z_value - min_z) / (float)(max_z - min_z);
	
	if (ratio <= 0.5f)
	{
		float t = ratio * 2.0f;
		r = (int)(189 + (255 - 189) * t);  // 189 -> 255
		g = (int)(147 + (121 - 147) * t);  // 147 -> 121
		b = (int)(249 + (198 - 249) * t);  // 249 -> 198
	}
	else
	{
		float t = (ratio - 0.5f) * 2.0f;
		r = (int)(255 + (139 - 255) * t);  // 255 -> 139
		g = (int)(121 + (233 - 121) * t);  // 121 -> 233
		b = (int)(198 + (253 - 198) * t);  // 198 -> 253
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