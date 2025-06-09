/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:44:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/09 19:13:35 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../libft/libft.h"
#include <stdio.h>

void init_point(t_point *point, int x, int y, char *value)
{
	point->x = x;
	point->y = y;
	point->z = ft_atoi(value);
	point->display[0] = 0;
	point->display[1] = 0;
	point->display[2] = 0;  // Initialize screen-space Z coordinate
	point->world_3d[0] = (double)x;
	point->world_3d[1] = (double)y;
	point->world_3d[2] = (double)point->z;
}