/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:32:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 02:58:12 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"
#include "../libft/libft.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);

void init_map(t_data *data, char *file_name)
{
    int map_file;
    int x;
    int y;
    char *map_row;
    char **row;

    x = 0;
    y = 0;
    data->map = ft_calloc(1, sizeof(t_map));
    map_file = open(file_name, O_RDONLY);
    if (map_file == -1)
        return;
    map_row = get_next_line(map_file);
    while(map_row)
    {
        x = 0;
        row = ft_split(map_row, ' ');
        if (row)
        {
            while(row[x])
            {
                if (y == 0)
                    data->map->map_width = x + 1;
                add_point(data, x, y, ft_atoi(row[x]));
                free(row[x]);
                x++;
            }
            free(row);
        }
        free(map_row);
        y++;
        data->map->map_height = y;
        map_row = get_next_line(map_file);
    }
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
