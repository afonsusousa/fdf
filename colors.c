/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 01:56:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 03:07:19 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

int get_color_from_z(int z_value, int min_z, int max_z)
{
	float ratio;
	float exponential_ratio;
	int r, g, b;
	
	// Aurora Borealis Gradient - The Most Beautiful Theme Ever!
	// Deep Ocean Blue → Electric Teal → Vibrant Green → Golden Yellow → Fiery Orange → Hot Pink
	
	if (max_z == min_z)
		ratio = 0.5f;
	else
		ratio = (float)(z_value - min_z) / (float)(max_z - min_z);
	
	// Apply exponential curve for more dramatic transitions
	exponential_ratio = powf(ratio, 1.8f);
	
	if (exponential_ratio <= 0.2f)
	{
		// Deep Ocean Blue → Electric Teal
		float t = exponential_ratio * 5.0f;
		r = (int)(13 + (0 - 13) * t);      // 13 → 0
		g = (int)(71 + (206 - 71) * t);    // 71 → 206
		b = (int)(161 + (209 - 161) * t);  // 161 → 209
	}
	else if (exponential_ratio <= 0.4f)
	{
		// Electric Teal → Vibrant Green
		float t = (exponential_ratio - 0.2f) * 5.0f;
		r = (int)(0 + (50 - 0) * t);       // 0 → 50
		g = (int)(206 + (255 - 206) * t);  // 206 → 255
		b = (int)(209 + (126 - 209) * t);  // 209 → 126
	}
	else if (exponential_ratio <= 0.6f)
	{
		// Vibrant Green → Golden Yellow
		float t = (exponential_ratio - 0.4f) * 5.0f;
		r = (int)(50 + (255 - 50) * t);    // 50 → 255
		g = (int)(255 + (223 - 255) * t);  // 255 → 223
		b = (int)(126 + (0 - 126) * t);    // 126 → 0
	}
	else if (exponential_ratio <= 0.8f)
	{
		// Golden Yellow → Fiery Orange
		float t = (exponential_ratio - 0.6f) * 5.0f;
		r = (int)(255 + (255 - 255) * t);  // 255 → 255
		g = (int)(223 + (69 - 223) * t);   // 223 → 69
		b = (int)(0 + (0 - 0) * t);        // 0 → 0
	}
	else
	{
		// Fiery Orange → Hot Pink
		float t = (exponential_ratio - 0.8f) * 5.0f;
		r = (int)(255 + (255 - 255) * t);  // 255 → 255
		g = (int)(69 + (20 - 69) * t);     // 69 → 20
		b = (int)(0 + (147 - 0) * t);      // 0 → 147
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