/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/11 00:59:57 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard_defines.h"

void	apply_auto_rotation(t_data *data)
{
	double	auto_rotation_speed;

	auto_rotation_speed = 0.01;
	if (data->view.chaos_mode)
	{
		data->view.alpha += auto_rotation_speed * 1.3;
		data->view.beta += auto_rotation_speed * 1.1;
		data->view.gamma += auto_rotation_speed * 1.3;
	}
	else
	{
		if (data->view.auto_rotate_x)
			data->view.alpha += auto_rotation_speed;
		if (data->view.auto_rotate_y)
			data->view.beta += auto_rotation_speed;
		if (data->view.auto_rotate_z)
			data->view.gamma += auto_rotation_speed;
	}
}

int	handle_rotation_keys(int keycode, t_data *data)
{
	double	rotation_step;

	rotation_step = 0.1;
	if (keycode == KEY_W)
		data->view.alpha -= rotation_step;
	else if (keycode == KEY_S)
		data->view.alpha += rotation_step;
	else if (keycode == KEY_A)
		data->view.beta -= rotation_step;
	else if (keycode == KEY_D)
		data->view.beta += rotation_step;
	else if (keycode == KEY_Z)
		data->view.gamma -= rotation_step;
	else if (keycode == KEY_X)
		data->view.gamma += rotation_step;
	else
		return (0);
	return (1);
}

int	handle_zoom_keys(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_EQUAL || keycode == KEY_NUMPAD_PLUS)
	{
		data->view.zoom += 2;
		if (data->view.zoom > 100)
			data->view.zoom = 100;
	}
	else if (keycode == KEY_MINUS)
	{
		data->view.zoom -= 2;
		if (data->view.zoom < 1)
			data->view.zoom = 1;
	}
	else
		return (0);
	return (1);
}

int	handle_scale_keys(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
	{
		data->view.scale += 0.05;
		if (data->view.scale > 5.0)
			data->view.scale = 5.0;
	}
	else if (keycode == KEY_PGDOWN)
	{
		data->view.scale -= 0.05;
		if (data->view.scale < 0.1)
			data->view.scale = 0.1;
	}
	else
		return (0);
	return (1);
}

int	handle_offset_keys(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->view.offset_y -= 20;
	else if (keycode == KEY_DOWN)
		data->view.offset_y += 20;
	else if (keycode == KEY_LEFT)
		data->view.offset_x -= 20;
	else if (keycode == KEY_RIGHT)
		data->view.offset_x += 20;
	else
		return (0);
	return (1);
}
