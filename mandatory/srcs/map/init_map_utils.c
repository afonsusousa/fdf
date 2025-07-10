/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:35:55 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 19:39:39 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_map_width(char **row)
{
	int	x;

	x = 0;
	while (row[x])
	{
		free(row[x]);
		x++;
	}
	return (x);
}

void	get_map_dimensions(t_data *data, int map_file)
{
	char	*map_row;
	char	**row;
	int		height;

	map_row = get_next_line(map_file);
	if (!map_row)
		return ;
	row = ft_split(map_row, ' ');
	if (row)
	{
		data->map->map_width = count_map_width(row);
		free(row);
	}
	free(map_row);
	height = 1;
	map_row = get_next_line(map_file);
	while (map_row)
	{
		free(map_row);
		map_row = get_next_line(map_file);
		height++;
	}
	data->map->map_height = height;
}

void	parse_map_row(t_data *data, char **row, int y)
{
	int		x;
	t_point	*point;

	x = 0;
	while (row[x] && x < data->map->map_width)
	{
		point = &data->map->points[y * data->map->map_width + x];
		init_point(point, x, y, row[x]);
		free(row[x]);
		x++;
	}
}

void	read_map_data(t_data *data, int map_file)
{
	char	*map_row;
	char	**row;
	int		y;

	y = 0;
	map_row = get_next_line(map_file);
	while (map_row)
	{
		row = ft_split(map_row, ' ');
		if (row)
		{
			parse_map_row(data, row, y);
			free(row);
		}
		free(map_row);
		map_row = get_next_line(map_file);
		y++;
	}
}
