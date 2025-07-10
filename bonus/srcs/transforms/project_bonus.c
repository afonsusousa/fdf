/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:50:11 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 18:01:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	project(t_data *data, t_point *point)
{
	if (data->view.view_mode != ORTOGRAPHIC)
	{
		point->display[0] = (int)((point->world_3d[0] - point->world_3d[1])
				* cos(data->view.angle));
		point->display[1] = (int)((point->world_3d[0] + point->world_3d[1])
				* sin(data->view.angle) - point->world_3d[2]);
	}
	else
	{
		point->display[0] = point->world_3d[0];
		point->display[1] = point->world_3d[1];
	}
}
