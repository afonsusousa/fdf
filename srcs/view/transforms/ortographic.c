/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ortographic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:36 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 18:20:47 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include "../../keyboard/keyboard.h"

void set_orthographic_view(t_data *data, int rotation_axis)
{
	double rotation_step = M_PI / 2.0; // 90 degrees
	
	if (rotation_axis == 0) // W key - Rotate around X axis (pitch up)
		data->view.alpha += rotation_step;
	else if (rotation_axis == 1) // S key - Rotate around X axis (pitch down)
		data->view.alpha -= rotation_step;
	else if (rotation_axis == 2) // A key - Rotate around Y axis (yaw left)
		data->view.beta -= rotation_step;
	else if (rotation_axis == 3) // D key - Rotate around Y axis (yaw right)
		data->view.beta += rotation_step;
	else if (rotation_axis == 4) // Z key - Rotate around Z axis (roll left)
		data->view.gamma += rotation_step;
	else if (rotation_axis == 5) // X key - Rotate around Z axis (roll right)
		data->view.gamma -= rotation_step;
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

void handle_orthographic_rotation(t_data *data, int key_index)
{
	if (data->view.view_mode != ORTOGRAPHIC)
		return;
	
	if (key_index == 0) // W key - Pitch up (rotate around X axis)
		set_orthographic_view(data, 0);
	else if (key_index == 1) // S key - Pitch down (rotate around X axis)
		set_orthographic_view(data, 1);
	else if (key_index == 2) // A key - Yaw left (rotate around Y axis)
		set_orthographic_view(data, 2);
	else if (key_index == 3) // D key - Yaw right (rotate around Y axis)
		set_orthographic_view(data, 3);
	else if (key_index == 4) // D key - Yaw right (rotate around Y axis)
		set_orthographic_view(data, 4);
	else if (key_index == 5) // D key - Yaw right (rotate around Y axis)
		set_orthographic_view(data, 5);
}

void ortographic_projection(t_data *data)
{
	if (data->view.view_mode == ISOMETRIC)
	{
		data->view.view_mode = ORTOGRAPHIC;
	}
	else
	{
		data->view.view_mode = ISOMETRIC;
	}
}