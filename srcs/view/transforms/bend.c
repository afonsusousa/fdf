/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bend.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:41:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 01:36:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

void bend(t_data *data, t_point *point)
{
	
	if (!data->view.bend || data->view.view_mode == ORTOGRAPHIC)
		return ;
	point->world_3d[2] -= ((point->x * point->x) * (data->view.brange)) 
				+ (point->y * point->y) * (data->view.brange);
}