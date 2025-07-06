/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:57:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 02:16:29 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "limits.h"
#include <math.h>

void	draw_steep(t_data *data, t_line *line)
{
	int				x;
	t_pixel_values	pixels;
	t_color			pixel_color;

	x = line->xpxl1;
	while (x <= line->xpxl2)
	{
		calculate_pixel_values(line, &pixels);
		pixel_color.color = get_interpolated_color(line, x);
		pixel_color.brightness = pixels.y_rfract;
		draw_pixel_color(data, pixels.y_pixel, x, &pixel_color);
		pixel_color.brightness = pixels.y_fract;
		draw_pixel_color(data, pixels.y_pixel + 1, x, &pixel_color);
		line->intersect_y += line->gradient;
		x++;
	}
}

void	draw_nonsteep(t_data *data, t_line *line)
{
	int				x;
	t_pixel_values	pixels;
	t_color			pixel_color;

	x = line->xpxl1;
	while (x <= line->xpxl2)
	{
		calculate_pixel_values(line, &pixels);
		pixel_color.color = get_interpolated_color(line, x);
		pixel_color.brightness = pixels.y_rfract;
		draw_pixel_color(data, x, pixels.y_pixel, &pixel_color);
		pixel_color.brightness = pixels.y_fract;
		draw_pixel_color(data, x, pixels.y_pixel + 1, &pixel_color);
		line->intersect_y += line->gradient;
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
