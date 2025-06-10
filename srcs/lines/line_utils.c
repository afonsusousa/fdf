/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:32:10 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 17:05:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

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
void init_line(t_line *line, int p0[2], int p1[2], int vz[2])
{
	int start[2] = {p0[0], p0[1]};
	int end[2] = {p1[0], p1[1]};
	int z_values[2] = {vz[0], vz[1]};
	
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
	}
	init_line_struct(line, start, end, z_values);
}