/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:57:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 02:58:43 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include "limits.h"
#include <math.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void init_line_struct(t_line *line, int p0[2], int p1[2], int vz[2])
{
	line->dx = p1[0] - p0[0];
	line->dy = p1[1] - p0[1];
	if (fabs(line->dx) < 0.001f)
		line->gradient = (line->dy > 0) ? 1000.0f : -1000.0f;
	else
		line->gradient = line->dy / line->dx;
	line->xpxl1 = p0[0];
	line->xpxl2 = p1[0];
	line->intersectY = (float)p0[1];
	line->z1 = vz[0];
	line->z2 = vz[1];
}
bool init_line(t_line *line, int p0[2], int p1[2], int vz[2])
{
	bool steep;
	int start[2] = {p0[0], p0[1]};
	int end[2] = {p1[0], p1[1]};
	int z_values[2] = {vz[0], vz[1]};
	
	steep = abs(end[1] - start[1]) > abs(end[0] - start[0]);
	if (steep)
	{
		swap(&start[0], &start[1]);
		swap(&end[0], &end[1]);
	}
	if (start[0] > end[0])
	{
		swap(&start[0], &end[0]);
		swap(&start[1], &end[1]);
		swap(&z_values[0], &z_values[1]);
	}
	init_line_struct(line, start, end, z_values);
	return (steep);
}

void draw_steep(t_data *data, t_line *line)
{
	int x;
	float y_fract;
	float y_rfract;
	int y_pixel;
	int current_color;

	x = line->xpxl1;
    while (x <= line->xpxl2)
    {
    	y_pixel = integer_of(line->intersectY);
    	y_fract = fractional_of(line->intersectY);
    	y_rfract = reverse_fractional_of(line->intersectY);
    	
    	if ((line->xpxl2 - line->xpxl1) == 0)
    		current_color = interpolate_color(line->color1, line->color2, 0.0f);
    	else
    		current_color = interpolate_color(line->color1, line->color2,
    			(float)(x - line->xpxl1) / (float)(line->xpxl2 - line->xpxl1));
        draw_pixel_color(data, y_pixel, x, current_color, y_rfract);
        draw_pixel_color(data, y_pixel + 1, x, current_color, y_fract);
        line->intersectY += line->gradient;
		x++;
    }
}

void draw_nonsteep(t_data *data, t_line *line)
{
	int x;
	float y_fract;
	float y_rfract;
	int y_pixel;
	int current_color;
	
	x = line->xpxl1;
    while (x <= line->xpxl2)
    {
		y_pixel = integer_of(line->intersectY);
       	y_fract = fractional_of(line->intersectY);
      	y_rfract = reverse_fractional_of(line->intersectY);
		if ((line->xpxl2 - line->xpxl1) == 0)
			current_color = interpolate_color(line->color1, line->color2, 0.0f);
		else
			current_color = interpolate_color(line->color1, line->color2,
				(float)(x - line->xpxl1) / (float)(line->xpxl2 - line->xpxl1));
        draw_pixel_color(data, x, y_pixel, current_color, y_rfract);
        draw_pixel_color(data, x, y_pixel + 1, current_color, y_fract);
        line->intersectY += line->gradient;
		x++;
    }
}

void set_line_color(t_line *line, t_data *data)
{
	line->color1 = get_color_from_z(line->z1,
				data->map->min_z * data->rotation.scale,
				data->map->max_z * data->rotation.scale);
	line->color2 = get_color_from_z(line->z2, 
				data->map->min_z * data->rotation.scale,
				data->map->max_z * data->rotation.scale);
}

void draw_line(t_data *data, int p0[2], int p1[2], int vz[2])
{
	t_line line;
	bool	steep;

	steep = init_line(&line, p0, p1, vz);
	set_line_color(&line, data);
	
	if (steep)
		draw_steep(data, &line);	
    else
		draw_nonsteep(data, &line);
}
