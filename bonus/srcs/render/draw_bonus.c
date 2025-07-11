/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:05:41 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 16:56:33 by amagno-r         ###   ########.fr       */
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
	if (color->s_rgba.a == 255)
		return (my_mlx_pixel_put(data, x, y, color->hex & 0xFFFFFF));
	if (color->s_rgba.a == 0)
		return ;
	final_color.s_rgba.r = (color->s_rgba.r * color->s_rgba.a) >> 8;
	final_color.s_rgba.g = (color->s_rgba.g * color->s_rgba.a) >> 8;
	final_color.s_rgba.b = (color->s_rgba.b * color->s_rgba.a) >> 8;
	final_color.s_rgba.a = 0;
	my_mlx_pixel_put(data, x, y, final_color.hex);
}

void	draw_background(t_data *data, int color)
{
	int	i;
	int	*dest;

	i = 0;
	dest = (int *)data->addr;
	while (i < data->pixel_count)
		dest[i++] = color;
}
