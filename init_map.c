/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:32:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 17:35:45 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include "../libft/libft.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);

static int count_map_width(char **row)
{
	int x;

	x = 0;
	while (row[x])
	{
		free(row[x]);
		x++;
	}
	return (x);
}

static void get_map_dimensions(t_data *data, int map_file)
{
	char *map_row;
	char **row;
	int height;

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
	while ((map_row = get_next_line(map_file)))
	{
		free(map_row);
		height++;
	}
	data->map->map_height = height;
}
static void parse_map_row(t_data *data, char **row, int y)
{
	int x;
	t_point *point;

	x = 0;
	while (row[x] && x < data->map->map_width)
	{
		point = &data->map->points[y * data->map->map_width + x];
		init_point(point, x, y, row[x]);
		free(row[x]);
		x++;
	}
}

static void read_map_data(t_data *data, int map_file)
{
	char *map_row;
	char **row;
	int y;

	y = 0;
	while ((map_row = get_next_line(map_file)))
	{
		row = ft_split(map_row, ' ');
		if (row)
		{
			parse_map_row(data, row, y);
			free(row);
		}
		free(map_row);
		y++;
	}
}

void init_map(t_data *data, char *file_name)
{
	int map_file;

	data->map = ft_calloc(1, sizeof(t_map));
	map_file = open(file_name, O_RDONLY);
	if (map_file == -1)
		return ;
	get_map_dimensions(data, map_file);
	close(map_file);
	data->map->points_count = data->map->map_width * data->map->map_height;
	data->map->points = ft_calloc(data->map->points_count, sizeof(t_point));
	map_file = open(file_name, O_RDONLY);
	read_map_data(data, map_file);
	close(map_file);
}

void map_set_limits(t_data *data)
{
    int min;
    int max;
    int x, y;
    t_point *current;

    if (!data || !data->map)
        return;

    min = INT_MAX;
    max = INT_MIN;
    
    for (y = 0; y < data->map->map_height; y++)
    {
        for (x = 0; x < data->map->map_width; x++)
        {
            current = get_point(data, x, y);
            if (current)
            {
                if(current->z < min)
                    min = current->z;
                if(current->z > max)
                    max = current->z;
            }
        }
    }
    data->map->min_z = min;
    data->map->max_z = max;
}
#include <stdio.h>
void print_map(t_data *data)
{
	int x, y;
	t_point *current;

	if (!data || !data->map)
		return;
	
	printf("Map dimensions: %d x %d\n", data->map->map_width, data->map->map_height);
	
	for (y = 0; y < data->map->map_height; y++)
	{
		for (x = 0; x < data->map->map_width; x++)
		{
			current = get_point(data, x, y);
			if (current)
				printf("%3d ", current->z);
			else
				printf("  0 ");
		}
		printf("\n");
	}
}
