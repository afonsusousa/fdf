/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:54:30 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 03:19:22 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	dvd(t_data *data)
{
	static int	dir_vector[2] = {1, 1};

	if (data->view.offset_y < 0)
	{
		data->view.offset_y = 0;
		dir_vector[1] = 1;
	}
	if (data->view.offset_y > data->w_height)
	{
		data->view.offset_y = data->w_height;
		dir_vector[1] = -1;
	}
	if (data->view.offset_x < data->m_width + 1)
	{
		data->view.offset_x = data->m_width + 1;
		dir_vector[0] = 1;
	}
	if (data->view.offset_x > data->w_width)
	{
		data->view.offset_x = data->w_width;
		dir_vector[0] = -1;
	}
	data->view.offset_x += dir_vector[0] * data->view.shift_step;
	data->view.offset_y += dir_vector[1] * data->view.shift_step;
}
