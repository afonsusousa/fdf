/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:32:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 19:48:27 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

void	init_map(t_data *data, char *file_name)
{
	int	map_file;

	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		return ;
	map_file = open(file_name, O_RDONLY);
	if (map_file == -1)
		return ;
	get_map_dimensions(data, map_file);
	close(map_file);
	data->map->points_count = data->map->map_width * data->map->map_height;
	data->map->points = ft_calloc(data->map->points_count, sizeof(t_point));
	if (!data->map->points)
		return (free(data->map));
	map_file = open(file_name, O_RDONLY);
	read_map_data(data, map_file);
	close(map_file);
	map_set_limits(data);
	colorize_points(data);
	center_coordinates(data);
}

void	process_row_limits(t_data *data, int y, int *min, int *max)
{
	int		x;
	t_point	*current;

	x = 0;
	while (x < data->map->map_width)
	{
		current = get_point(data, x, y);
		if (current)
		{
			if (current->z < *min)
				*min = current->z;
			if (current->z > *max)
				*max = current->z;
		}
		x++;
	}
}

void	map_set_limits(t_data *data)
{
	int	y;
	int	min;
	int	max;

	if (!data || !data->map)
		return ;
	min = INT_MAX;
	max = INT_MIN;
	y = 0;
	while (y < data->map->map_height)
	{
		process_row_limits(data, y, &min, &max);
		y++;
	}
	data->map->min_z = min;
	data->map->max_z = max;
}

void	print_map_row(t_data *data, int y)
{
	int		x;
	t_point	*current;

	x = 0;
	while (x < data->map->map_width)
	{
		current = get_point(data, x, y);
		if (current)
			printf("%3d ", current->z);
		else
			printf("  0 ");
		x++;
	}
	printf("\n");
}

void	print_map(t_data *data)
{
	int	y;

	if (!data || !data->map)
		return ;
	printf("Map dimensions: %d x %d\n", data->map->map_width,
		data->map->map_height);
	y = 0;
	while (y < data->map->map_height)
	{
		print_map_row(data, y);
		y++;
	}
}
