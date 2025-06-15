/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_priority.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 03:40:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 17:36:16 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float calculate_line_depth(t_line_info *line, t_view *view)
{
    double midpoint_z = ((1 / view->scale) 
						* (line->p0->world_3d[2] + line->p1->world_3d[2]))
					 	/ 2.0;
    if (view->top_down && view->render_mode == RENDER_BRAINFUCK_PRIORITY)
         return (midpoint_z);  
    return (-midpoint_z); 
}

void draw_lines_priority(t_data *data)
{
	int line_count;
	int capacity;
	int i;
	
	if(data->map->lines)
		free_and_null(&data->map->lines);
	capacity = data->map->map_width * data->map->map_height * 2;
	data->map->lines = (t_line_info *)malloc(capacity * sizeof(t_line_info));
	if (!data->map->lines)
		return ;
	line_count = collect_lines(data, data->map->lines);
	if (line_count == 0)
		return free_and_null(&data->map->lines);
	i = -1;
	while (++i < line_count)
		data->map->lines[i].depth = calculate_line_depth(&data->map->lines[i],
			 &data->view);
	quick_sort_lines(data->map->lines, 0, line_count - 1);
	i = -1;
	while (++i < line_count)
		draw_line_with_offset(data, data->map->lines[i].p0,
			data->map->lines[i].p1);
	free_and_null(&data->map->lines);
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

