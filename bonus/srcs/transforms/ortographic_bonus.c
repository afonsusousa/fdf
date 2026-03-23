/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ortographic_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:36 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	normalize_orto_angles(t_data *data)
{
	while (data->view.alpha > 2 * M_PI)
		data->view.alpha -= 2 * M_PI;
	while (data->view.alpha < -2 * M_PI)
		data->view.alpha += 2 * M_PI;
	while (data->view.beta > 2 * M_PI)
		data->view.beta -= 2 * M_PI;
	while (data->view.beta < -2 * M_PI)
		data->view.beta += 2 * M_PI;
	while (data->view.gamma > 2 * M_PI)
		data->view.gamma -= 2 * M_PI;
	while (data->view.gamma < -2 * M_PI)
		data->view.gamma += 2 * M_PI;
}

void	set_orthographic_view(t_data *data, int rotation_axis)
{
	double	r_step;

	r_step = M_PI / 2.0;
	if (rotation_axis == 0)
		data->view.alpha += r_step;
	else if (rotation_axis == 1)
		data->view.alpha -= r_step;
	else if (rotation_axis == 2)
		data->view.beta -= r_step;
	else if (rotation_axis == 3)
		data->view.beta += r_step;
	else if (rotation_axis == 4)
		data->view.gamma += r_step;
	else if (rotation_axis == 5)
		data->view.gamma -= r_step;
	normalize_orto_angles(data);
}

void	handle_orthographic_rotation(t_data *data, int key_index)
{
	if (data->view.view_mode != ORTOGRAPHIC)
		return ;
	if (key_index == 0)
		set_orthographic_view(data, 0);
	else if (key_index == 1)
		set_orthographic_view(data, 1);
	else if (key_index == 2)
		set_orthographic_view(data, 2);
	else if (key_index == 3)
		set_orthographic_view(data, 3);
	else if (key_index == 4)
		set_orthographic_view(data, 4);
	else if (key_index == 5)
		set_orthographic_view(data, 5);
}
