/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:44:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 15:35:52 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../libft/libft.h"

size_t pntlen(t_point *pnt)
{
    size_t len;

    if (!pnt)
        return (0);
    len = 0;
    while (pnt[len].last == false)
        len++;
    return (len);
}
void copy_point(t_point *dest, t_point src)
{
	dest->x = src.x;
	dest->y = src.y;
	dest->z = src.z;
	dest->last = src.last;
}

t_point *pntjoin(t_point *dest, t_point p2)
{
	size_t 	i;
	size_t	len;
	t_point	*ret;

	if (!dest)
		return (0);
	i = 0;
	len = pntlen(dest) + 1;
	ret = (t_point *)ft_calloc(len, sizeof(t_point));
	if (!ret)
		return (NULL);
	while (i < len - 1)
	{
		dest[i].last = false;
		copy_point(&ret[i], dest[i]);
		i++;
	}
	copy_point(&ret[i], p2);
	return (ret);
}

void add_point(t_data *data, int x, int y, int z)
{
    t_point new_point;

    new_point.x = x;
    new_point.y = y;
    new_point.z = z;
	new_point.last = true;

    if(!data->map->map)
    {
		data->map->map = ft_calloc(1, sizeof(t_point));
		copy_point(&data->map->map[0], new_point);
        return ;
    }
    else
        data->map->map = pntjoin(data->map->map, new_point);
}