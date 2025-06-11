/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:03:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/11 01:15:33 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <stdlib.h>
#include <math.h>

float	get_line_plane_distance(t_line_info *line, float plane_z)
{
	float	z1;
	float	z2;
	float	min_z;
	float	max_z;

	z1 = line->p0->world_3d[2];
	z2 = line->p1->world_3d[2];
	if (z1 > z2)
	{
		min_z = z2;
		max_z = z1;
	}
	else
	{
		min_z = z1;
		max_z = z2;
	}
	if (plane_z >= min_z && plane_z <= max_z)
		return (0.0f);
	return (min_z - plane_z);
}

int	line_intersects_plane(t_line_info *line, float plane_z)
{
	float	z1;
	float	z2;
	float	mid_z;

	z1 = line->p0->world_3d[2];
	z2 = line->p1->world_3d[2];
	mid_z = (z1 + z2) / 2.0f;
	return (fabs(mid_z - plane_z) < 0.5f);
}

void	get_depth_bounds(t_data *data, float *min_z, float *max_z)
{
	int		x;
	int		y;
	t_point	*point;

	*min_z = 999999.0f;
	*max_z = -999999.0f;
	y = 0;
	while (y < data->map->map_height)
	{
		x = 0;
		while (x < data->map->map_width)
		{
			point = get_point(data, x, y);
			if (point)
			{
				if (point->world_3d[2] < *min_z)
					*min_z = point->world_3d[2];
				if (point->world_3d[2] > *max_z)
					*max_z = point->world_3d[2];
			}
			x++;
		}
		y++;
	}
}

void	assign_lines_to_depths(t_line_info *lines, int line_count, 
	float min_z, float max_z, int num_layers)
{
	int	i;
	float	depth_range;
	float	mid_z;
	int	layer;

	depth_range = max_z - min_z;
	if (depth_range < 0.001f)
		depth_range = 0.001f;
	i = 0;
	while (i < line_count)
	{
		mid_z = (lines[i].p0->world_3d[2] + lines[i].p1->world_3d[2]) / 2.0f;
		layer = (int)((mid_z - min_z) / depth_range * (num_layers - 1));
		if (layer < 0)
			layer = 0;
		if (layer >= num_layers)
			layer = num_layers - 1;
		lines[i].depth = layer;
		i++;
	}
}

void	render_depth_layer(t_data *data, t_line_info *lines, 
	int line_count, int target_layer)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if ((int)lines[i].depth == target_layer)
			draw_line_with_offset(data, lines[i].p0, lines[i].p1);
		i++;
	}
}

void	draw_lines_plane_sweep(t_data *data)
{
	t_line_info	*lines;
	int		line_count;
	int		capacity;
	float		min_z;
	float		max_z;
	int		num_layers;
	int		layer;

	capacity = data->map->map_width * data->map->map_height * 2;
	lines = (t_line_info *)malloc(capacity * sizeof(t_line_info));
	if (!lines)
		return ;
	line_count = collect_lines(data, lines);
	if (line_count == 0)
		return (free(lines));
	get_depth_bounds(data, &min_z, &max_z);
	num_layers = 50;
	assign_lines_to_depths(lines, line_count, min_z, max_z, num_layers);
	if (data->view.top_down)
	{
		layer = num_layers - 1;
		while (layer >= 0)
		{
			render_depth_layer(data, lines, line_count, layer);
			layer--;
		}
	}
	else
	{
		layer = 0;
		while (layer < num_layers)
		{
			render_depth_layer(data, lines, line_count, layer);
			layer++;
		}
	}
	free(lines);
}

