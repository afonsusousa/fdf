/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_press.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 03:02:15 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

void	apply_auto_rotation(t_data *data)
{
	double	auto_rotation_speed;

	auto_rotation_speed = 0.005;
	if (data->view.auto_rotate == 8)
	{
		data->view.alpha += auto_rotation_speed * 1.3;
		data->view.beta += auto_rotation_speed * 1.1;
		data->view.gamma += auto_rotation_speed * 1.3;
	}
	else
	{
		if (data->view.auto_rotate & 4)
			data->view.alpha += auto_rotation_speed;
		if (data->view.auto_rotate & 2)
			data->view.beta += auto_rotation_speed;
		if (data->view.auto_rotate & 1)
			data->view.gamma += auto_rotation_speed;
	}
}

static int	handle_rotation_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[KEY_INDEX_W] = 1;
	else if (keycode == KEY_S)
		data->keys[KEY_INDEX_S] = 1;
	else if (keycode == KEY_A)
		data->keys[KEY_INDEX_A] = 1;
	else if (keycode == KEY_D)
		data->keys[KEY_INDEX_D] = 1;
	else if (keycode == KEY_Z)
		data->keys[KEY_INDEX_Z] = 1;
	else if (keycode == KEY_X)
		data->keys[KEY_INDEX_X] = 1;
	else
		return (0);
	return (1);
}

static int	handle_zoom_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_NUMPAD_PLUS)
		data->keys[KEY_INDEX_PLUS] = 1;
	else if (keycode == KEY_MINUS)
		data->keys[KEY_INDEX_MINUS] = 1;
	else
		return (0);
	return (1);
}

static int	handle_scale_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
		data->keys[KEY_INDEX_PGUP] = 1;
	else if (keycode == KEY_PGDOWN)
		data->keys[KEY_INDEX_PGDOWN] = 1;
	else
		return (0);
	return (1);
}

static int	handle_shift_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->keys[KEY_INDEX_UP] = 1;
	else if (keycode == KEY_DOWN)
		data->keys[KEY_INDEX_DOWN] = 1;
	else if (keycode == KEY_LEFT)
		data->keys[KEY_INDEX_LEFT] = 1;
	else if (keycode == KEY_RIGHT)
		data->keys[KEY_INDEX_RIGHT] = 1;
	else
		return (0);
	return (1);
}

int	handle_view_keypress(int keycode, t_data *data)
{
	handle_rotation_keypress(keycode, data);
	handle_zoom_keypress(keycode, data);
	handle_scale_keypress(keycode, data);
	handle_shift_keypress(keycode, data);
	return (1);
}
