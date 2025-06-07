/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:44:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 16:54:26 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../libft/libft.h"
#include <stdio.h>

size_t pntlen(t_data *data)
{
    if (!data || !data->map)
        return (0);
    return (data->map->points_count);
}

void copy_point(t_point *dest, t_point src)
{
	dest->x = src.x;
	dest->y = src.y;
	dest->z = src.z;
}

t_point *pntjoin(t_data *data, t_point *dest, t_point p2)
{
	size_t 	i;
	size_t	current_len;
	t_point	*ret;

	if (!dest)
	{
		ret = (t_point *)ft_calloc(1, sizeof(t_point));
		if (!ret)
			return (NULL);
		copy_point(&ret[0], p2);
		return (ret);
	}
	current_len = pntlen(data);
	ret = (t_point *)ft_calloc(current_len + 1, sizeof(t_point));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < current_len)
	{
		copy_point(&ret[i], dest[i]);
		i++;
	}
	copy_point(&ret[i], p2);
	return (ret);
}

void add_point(t_data *data, int x, int y, int z)
{
    t_point new_point;
    t_point *old_map;

    new_point.x = x;
    new_point.y = y;
    new_point.z = z;

    if(!data->map->points)
    {
		data->map->points = ft_calloc(1, sizeof(t_point));
		copy_point(&data->map->points[0], new_point);
		data->map->points_count = 1;
        return ;
    }
    else
    {
        old_map = data->map->points;
        data->map->points = pntjoin(data, old_map, new_point);
        if (data->map->points)
        {
            free(old_map);
            data->map->points_count++;
        }
        else
        {
            data->map->points = old_map; // Restore old map
        }
    }
}