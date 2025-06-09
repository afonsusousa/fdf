/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:05:41 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 02:11:41 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return;
	if (!data || !data->addr)
		return;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_pixel(t_data *data, int x, int y, float brightness)
{
	int color;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return;
	if (!data)
		return;
	if (brightness < 0.0f)
		brightness = 0.0f;
	if (brightness > 1.0f)
		brightness = 1.0f;
	int gray_value = (int)(brightness * 255);
	color = gray_value << 16 | gray_value << 8 | gray_value;
	my_mlx_pixel_put(data, x, y, color);
}
void draw_horizontal(t_data *img, int offset_x, int offset_y)
{
	int height;
	int width;
	t_point *row;
	t_point *p1;
	t_point *p2;

	height = img->map->map_height;
	width = img->map->map_width;
	for (int y = 0; y < height; y++)
	{
		row = &img->map->points[y * width];
		for (int x = 0; x < width - 1; x++)
		{
			p1 = &row[x];
			p2 = &row[x + 1];
			int start[2] = {p1->display[0] + offset_x, p1->display[1] + offset_y};
			int end[2] = {p2->display[0] + offset_x, p2->display[1] + offset_y};
			int vz[2] = {p1->z, p2->z};  // Pass Z values for gradient
			draw_line(img, start, end, vz);
		}
	}
}

void draw_vertical(t_data *img, int offset_x, int offset_y)
{
	int height;
	int width;
	t_point *p1;
	t_point *p2;

	height = img->map->map_height;
	width = img->map->map_width;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height - 1; y++)
		{
			p1 = &img->map->points[y * width + x];		// Current point
			p2 = &img->map->points[(y + 1) * width + x]; // Point below
			int start[2] = {p1->display[0] + offset_x, p1->display[1] + offset_y};
			int end[2] = {p2->display[0] + offset_x, p2->display[1] + offset_y};
			int vz[2] = {p1->z, p2->z};  // Pass Z values for gradient
			draw_line(img, start, end, vz);
		}
	}
}

// Color utility functions for gradient drawing


void draw_pixel_color(t_data *data, int x, int y, int color, float brightness)
{
	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return;
	if (!data)
		return;
	if (brightness < 0.0f)
		brightness = 0.0f;
	if (brightness > 1.0f)
		brightness = 1.0f;
	
	int r = ((color >> 16) & 0xFF) * brightness;
	int g = ((color >> 8) & 0xFF) * brightness;
	int b = (color & 0xFF) * brightness;
	
	int final_color = (r << 16) | (g << 8) | b;
	my_mlx_pixel_put(data, x, y, final_color);
}