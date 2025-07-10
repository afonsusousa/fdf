/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 01:53:43 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 02:22:37 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    orbit(double *world_3d, t_data *data)
{
    double radius_x = data->map->map_width / 2.0;
    double radius_y = data->map->map_height / 2.0;
    double x_diff = radius_x * cos(data->time);
    double y_diff = radius_y * sin(data->time);

    world_3d[0] += x_diff;
    world_3d[1] += y_diff;
}