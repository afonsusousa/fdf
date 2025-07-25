/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:54:30 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 18:21:49 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dvd(t_data *data)
{
	static int	dir[2] = {1, 1};

	if (data->view.off_y < 0)
	{
		data->view.off_y = 0;
		dir[1] = 1;
	}
	if (data->view.off_y > data->w_height)
	{
		data->view.off_y = data->w_height;
		dir[1] = -1;
	}
	if (data->view.off_x < data->m_width + 1)
	{
		data->view.off_x = data->m_width + 1;
		dir[0] = 1;
	}
	if (data->view.off_x > data->w_width)
	{
		data->view.off_x = data->w_width;
		dir[0] = -1;
	}
	data->view.off_x += dir[0] * data->view.sh_step * log10(data->view.zoom);
	data->view.off_y += dir[1] * data->view.sh_step * log10(data->view.zoom);
}
