/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:07:39 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 19:08:26 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void free_data(t_data *data)
{
	if (data->map->points)
		free(data->map->points);
	if (data->map->lines)
		free(data->map->lines);
	free(data->map);
	free(data->mlx);
	free(data->mlx_win);
	free(data->img);
}