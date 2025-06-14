/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:05:41 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:53:18 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include "../libft/libft.h"

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

void draw_background(t_data *data, int color)
{
	unsigned int i;
	unsigned int pixel_count;
	int *dest;

	i = 0;
	pixel_count = data->window_height * data->window_width;
	dest = (int *) data->addr;
	while (i < pixel_count)
		dest[i++] = color;
}