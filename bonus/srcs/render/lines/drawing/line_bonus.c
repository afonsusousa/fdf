/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:57:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 16:56:33 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "limits.h"
#include <math.h>

static void	draw_steep(t_data *data, t_line *line)
{
	int				x;
	t_pixel_values	pixels;
	t_color			color;

	x = line->x_start;
	while (x <= line->x_end)
	{
		calculate_pixel_values(line, &pixels);
		color.hex = get_interpolated_color(line, x);
		color.s_rgba.a = (unsigned char)(pixels.y_rfract * 255);
		draw_pixel_color(data, pixels.y_pixel, x, &color);
		color.s_rgba.a = (unsigned char)(pixels.y_fract * 255);
		draw_pixel_color(data, pixels.y_pixel + 1, x, &color);
		line->current_y += line->slope;
		x++;
	}
}

static void	draw_nonsteep(t_data *data, t_line *line)
{
	int				x;
	t_pixel_values	pixels;
	t_color			color;

	x = line->x_start;
	while (x <= line->x_end)
	{
		calculate_pixel_values(line, &pixels);
		color.hex = get_interpolated_color(line, x);
		color.s_rgba.a = (unsigned char)(pixels.y_rfract * 255);
		draw_pixel_color(data, x, pixels.y_pixel, &color);
		color.s_rgba.a = (unsigned char)(pixels.y_fract * 255);
		draw_pixel_color(data, x, pixels.y_pixel + 1, &color);
		line->current_y += line->slope;
		x++;
	}
}

void	draw_line_screen_only(t_data *data, t_point *p0, t_point *p1)
{
	t_line	line;

	init_line(data, &line, p0, p1);
	if ((in_screen(data, p0) || in_screen(data, p1)))
	{
		if (line.steep)
			draw_steep(data, &line);
		else
			draw_nonsteep(data, &line);
	}
}

void	draw_line_with_offset(t_data *data, t_point *p0, t_point *p1)
{
	t_line	line;

	init_line(data, &line, p0, p1);
	if (line.steep)
		draw_steep(data, &line);
	else
		draw_nonsteep(data, &line);
}
