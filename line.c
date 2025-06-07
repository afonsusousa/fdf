/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:57:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 19:48:47 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include <math.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void init_line_struct(t_line *line, t_coords *p0, t_coords *p1)
{
	line->dx = p1->x - p0->x;
	line->dy = p1->y - p0->y;
	if (line->dx == 0.0)
		line->gradient = 1;
	else
		line->gradient = line->dy / line->dx;
	line->xpxl1 = p0->x;
	line->xpxl2 = p1->x;
	line->intersectY = p0->y;
}
void init_line(t_line *line, t_coords *p0, t_coords *p1, int *steep)
{
	*steep = abs(p1->y - p0->y) > abs(p1->x - p0->x);
	if (steep)
	{
		swap(&p0->x, &p0->y);
		swap(&p1->x, &p1->y);
	}
	if (p0->x > p1->x)
	{
		swap(&p0->x, &p1->x);
		swap(&p0->y, &p1->y);
	}
	init_line_struct(line, p0, p1);
}
void draw_line(t_data *data, t_coords *p0, t_coords *p1)
{
	int steep;
	int x;
	t_line line;
	
	init_line(&line, p0, p1, &steep);
	 if (steep)
    {
        x = line.xpxl1;
        while (x <= line.xpxl2)
        {
            draw_pixel(data, integer_of(line.intersectY), x,
                fractional_of(line.intersectY));
            draw_pixel(data, integer_of(line.intersectY) - 1, x,
                reverse_fractional_of(line.intersectY));
            line.intersectY += line.gradient;
			x++;
        }
    }
    else
    {
        x = line.xpxl1;
        while (x <= line.xpxl2)
        {
            draw_pixel(data, x, integer_of(line.intersectY),
                reverse_fractional_of(line.intersectY));
            draw_pixel(data, x, integer_of(line.intersectY) - 1,
                fractional_of(line.intersectY));
            line.intersectY += line.gradient;
			x++;
        }
    }
}