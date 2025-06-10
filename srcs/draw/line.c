/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:57:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 16:26:42 by amagno-r         ###   ########.fr       */
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

void draw_line(t_data *data, t_point *p0, t_point *p1)
{
	t_line line;
	int z_vector[2];
	bool	steep;

	z_vector[0] = p0->z;
	z_vector[1] = p1->z;
	steep = init_line(&line, p0->display, p1->display, z_vector);
	set_line_color(&line, data);
	
	if (steep)
		draw_steep(data, &line);	
    else
		draw_nonsteep(data, &line);
}

void draw_line_with_offset(t_data *data, t_point *p0, t_point *p1)
{
	t_line line;
	int z_vector[2];
	int p0_coords[2];
	int p1_coords[2];
	bool	steep;

	p0_coords[0] = p0->display[0] + data->view.offset_x;
	p0_coords[1] = p0->display[1] + data->view.offset_y;
	p1_coords[0] = p1->display[0] + data->view.offset_x;
	p1_coords[1] = p1->display[1] + data->view.offset_y;
	
	z_vector[0] = p0->z;
	z_vector[1] = p1->z;
	steep = init_line(&line, p0_coords, p1_coords, z_vector);
	set_line_color(&line, data);
	if (steep)
		draw_steep(data, &line);	
    else
		draw_nonsteep(data, &line);
}
