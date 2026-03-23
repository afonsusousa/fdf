/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:07:39 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 19:58:38 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_null(t_line_info **address)
{
	free(*address);
	*address = NULL;
}

void	free_strs(char **strs, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (strs[i])
			free(strs[i]);
}

void	free_data(t_data *data)
{
	if (data->map->points)
		free(data->map->points);
	if (data->map->lines)
		free(data->map->lines);
	free(data->map);
	if (data->mlx && data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx && data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	exit(0);
}
