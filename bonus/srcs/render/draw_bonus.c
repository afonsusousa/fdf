/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:05:41 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 00:18:18 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	if (!data || !data->addr)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_pixel_color(t_data *data, int x, int y, t_color *color)
{
	t_color	final_color;

	if (x < 0 || y < 0 || x >= 1920 || y >= 1080)
		return ;
	if (!data || !color)
		return ;
	if (color->rgba.a == 255)
		return (my_mlx_pixel_put(data, x, y, color->hex & 0xFFFFFF));
	if (color->rgba.a == 0)
		return ;
	final_color.rgba.r = (color->rgba.r * color->rgba.a) >> 8;
	final_color.rgba.g = (color->rgba.g * color->rgba.a) >> 8;
	final_color.rgba.b = (color->rgba.b * color->rgba.a) >> 8;
	final_color.rgba.a = 0;
	my_mlx_pixel_put(data, x, y, final_color.hex);
}

void	draw_background(t_data *data, int color)
{
	int	i;
	int				*dest;

	i = 0;
	dest = (int *)data->addr;
	while (i < data->pixel_count)
		dest[i++] = color;
}
