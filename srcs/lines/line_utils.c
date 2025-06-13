/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:32:10 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 21:55:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void init_line_struct(t_line *line, int p0[2], int p1[2])
{
	line->dx = p1[0] - p0[0];
	line->dy = p1[1] - p0[1];
	if (fabs(line->dx) < 0.001f)
	{
		if (line->dy > 0)
			line->gradient = 1000.0f;
		else
			line->gradient = -1000.0f;
	}
	else
		line->gradient = line->dy / line->dx;
	line->xpxl1 = p0[0];
	line->xpxl2 = p1[0];
	line->intersectY = (float)p0[1];
}
void init_line(t_data *data, t_line *line, t_point *p0, t_point *p1)
{
	bool swapped;

	swapped = false;
	int start[2] = {p0->display[0] + data->view.offset_x, p0->display[1] + data->view.offset_y};
	int end[2] = {p1->display[0] + data->view.offset_x, p1->display[1] + data->view.offset_y};
	int z_values[2] = {p0->z, p1->z};

	line->steep = abs(end[1] - start[1]) > abs(end[0] - start[0]);
	if (line->steep)
	{
		swap(&start[0], &start[1]);
		swap(&end[0], &end[1]);
	}
	if (start[0] > end[0])
	{
		swap(&start[0], &end[0]);
		swap(&start[1], &end[1]);
		swap(&z_values[0], &z_values[1]);
		swapped = true;
	}
	init_line_struct(line, start, end);
	line->color1 = get_color_from_z(z_values[0], data->map->min_z, data->map->max_z);
	line->color2 = get_color_from_z(z_values[1], data->map->min_z, data->map->max_z);
	if (p0->paint || p1->paint)
	{
		line->color1 = (p0->color * !swapped) + (p1->color * swapped);
		line->color2 = (p1->color * !swapped) + (p0->color * swapped);
	}
}
