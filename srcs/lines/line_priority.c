/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_priority.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 03:40:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/11 01:43:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float calculate_line_depth(t_line_info *line, t_view *view)
{
    double midpoint_z = (line->p0->world_3d[2] + line->p1->world_3d[2]) / 2.0;
    
    if (!view->top_down && view->brainfuck_priority)
         return (midpoint_z);  
    return (-midpoint_z);  
}

int compare_depth(const void *a, const void *b)
{
	t_line_info *line_a;
	t_line_info *line_b;
	double depth_diff;
	
	line_a = (t_line_info *)a;
	line_b = (t_line_info *)b;
	
	depth_diff = line_b->depth - line_a->depth;
	if (depth_diff > 0)
		return (1);
	else if (depth_diff < 0)
		return (-1);
	
	return (0);
}

void draw_lines_priority(t_data *data)
{
	t_line_info *lines;
	int line_count;
	int capacity;
	int i;
	
	capacity = data->map->map_width * data->map->map_height * 2;
	lines = (t_line_info *)malloc(capacity * sizeof(t_line_info));
	if (!lines)
		return ;
	line_count = collect_lines(data, lines);
	if (line_count == 0)
		return free(lines);
	i = -1;
	while (++i < line_count)
		lines[i].depth = calculate_line_depth(&lines[i], &data->view);
	qsort(lines, line_count, sizeof(t_line_info), compare_depth);
	i = -1;
	while (++i < line_count)
		draw_line_with_offset(data, lines[i].p0, lines[i].p1);
	free(lines);
}

void add_line_data(t_line_info *line, t_point *p0, t_point *p1)
{
	line->p0 = p0;
	line->p1 = p1;
}

int collect_horizontal_lines(t_data *data, t_line_info *lines)
{
	int x;
	int y;
	int line_index;
	t_point *current;
	t_point *right;

	line_index = 0;
	y = 0;
	while (y < data->map->map_height)
	{
		x = 0;
		while (x < data->map->map_width - 1)
		{
			current = get_point(data, x, y);
			right = get_point(data, x + 1, y);
			if (current && right)
			{
				add_line_data(&lines[line_index], current, right);
				line_index++;
			}
			x++;
		}
		y++;
	}
	return (line_index);
}

int collect_vertical_lines(t_data *data, t_line_info *lines, int start)
{
	int x;
	int y;
	int line_index;
	t_point *current;
	t_point *down;

	line_index = start;
	y = 0;
	while (y < data->map->map_height - 1)
	{
		x = 0;
		while (x < data->map->map_width)
		{
			current = get_point(data, x, y);
			down = get_point(data, x, y + 1);
			if (current && down)
			{
				add_line_data(&lines[line_index], current, down);
				line_index++;
			}
			x++;
		}
		y++;
	}
	return (line_index);
}

int collect_lines(t_data *data, t_line_info *lines)
{
	int line_count;

	line_count = collect_horizontal_lines(data, lines);
	line_count = collect_vertical_lines(data, lines, line_count);
	return (line_count);
}

