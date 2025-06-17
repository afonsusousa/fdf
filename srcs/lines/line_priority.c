/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_priority.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 03:40:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 17:42:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float	calculate_line_depth(t_line_info *line, t_view *view)
{
	double	midpoint_z;

	midpoint_z = ((1 / view->scale) * (line->p0->world_3d[2]
				+ line->p1->world_3d[2])) / 2.0;
	if (view->top_down && view->render_mode == RENDER_BRAINFUCK_PRIORITY)
		return (midpoint_z);
	return (-midpoint_z);
}

void	draw_lines_priority(t_data *data)
{
	int	line_count;
	int	i;

	if (data->map->lines)
		free_and_null(&data->map->lines);
	data->map->lines = (t_line_info *)malloc(data->map->line_capacity
			* sizeof(t_line_info));
	if (!data->map->lines)
		return (free_data(data));
	line_count = collect_lines(data, data->map->lines);
	if (line_count == 0)
		return (free_and_null(&data->map->lines), free_data(data));
	i = -1;
	while (++i < line_count)
		data->map->lines[i].depth = calculate_line_depth(&data->map->lines[i],
				&data->view);
	if (!merge_sort_lines(data->map->lines, 0, line_count - 1))
		return (free_data(data));
	i = -1;
	while (++i < line_count)
		draw_line_with_offset(data, data->map->lines[i].p0,
			data->map->lines[i].p1);
	free_and_null(&data->map->lines);
}

int	collect_horizontal_lines(t_data *data, t_line_info *lines)
{
	int		x;
	int		y;
	int		line_index;
	t_point	*curr;
	t_point	*r;

	line_index = 0;
	y = 0;
	while (y < data->map->map_height)
	{
		x = -1;
		while (++x < data->map->map_width - 1)
		{
			curr = get_point(data, x, y);
			r = get_point(data, x + 1, y);
			if (curr && r && (in_screen(data, curr) || in_screen(data, r)))
			{
				lines[line_index].p0 = curr;
				lines[line_index].p1 = r;
				line_index++;
			}
		}
		y++;
	}
	return (line_index);
}

int	collect_vertical_lines(t_data *data, t_line_info *lines, int start)
{
	int		x;
	int		y;
	int		line_index;
	t_point	*curr;
	t_point	*d;

	line_index = start;
	y = 0;
	while (y < data->map->map_height - 1)
	{
		x = -1;
		while (++x < data->map->map_width)
		{
			curr = get_point(data, x, y);
			d = get_point(data, x, y + 1);
			if (curr && d && (in_screen(data, curr) || in_screen(data, d)))
			{
				lines[line_index].p0 = curr;
				lines[line_index].p1 = d;
				line_index++;
			}
		}
		y++;
	}
	return (line_index);
}

int	collect_lines(t_data *data, t_line_info *lines)
{
	int	line_count;

	line_count = collect_horizontal_lines(data, lines);
	line_count = collect_vertical_lines(data, lines, line_count);
	return (line_count);
}
