/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bend.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:41:09 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/18 21:50:17 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

void bend(t_data *data, t_point *point)
{
	(void) data;
	float bend;
	if (data->view.range == 0.0)
		return ;
	bend = ((point->x * point->x) * (data->view.range)) 
	+ (point->y * point->y) * (data->view.range);
	point->world_3d[2] -= bend;
}