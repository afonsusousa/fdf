/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:32:10 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 23:12:29 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_line_struct(t_line *line, int p0[2], int p1[2])
{
	line->dx = p1[0] - p0[0];
	line->dy = p1[1] - p0[1];
	if (fabs(line->dx) < 0.001f)
	{
		if (line->dy > 0)
			line->slope = 1000.0f;
		else
			line->slope = -1000.0f;
	}
	else
		line->slope = line->dy / line->dx;
	line->x_start = p0[0];
	line->x_end = p1[0];
	line->current_y = (float)p0[1];
}

static bool	prepare_line_endpoints(int start[2], int end[2], int z_values[2],
		bool *steep)
{
	bool	swapped;

	swapped = false;
	*steep = abs(end[1] - start[1]) > abs(end[0] - start[0]);
	if (*steep)
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
	return (swapped);
}

void	init_line(t_data *data, t_line *line, t_point *p0, t_point *p1)
{
	bool	swapped;
	int		start[2];
	int		end[2];
	int		z_values[2];

	start[0] = p0->display[0] + data->view.off_x;
	start[1] = p0->display[1] + data->view.off_y;
	end[0] = p1->display[0] + data->view.off_x;
	end[1] = p1->display[1] + data->view.off_y;
	z_values[0] = p0->z;
	z_values[1] = p1->z;
	swapped = prepare_line_endpoints(start, end, z_values, &line->steep);
	init_line_struct(line, start, end);
	if (!swapped)
	{
		line->color1 = p0->color;
		line->color2 = p1->color;
	}
	else
	{
		line->color1 = p1->color;
		line->color2 = p0->color;
	}
}
