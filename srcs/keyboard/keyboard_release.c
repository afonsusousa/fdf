/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:17:22 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/12 17:27:08 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

static int	handle_rotation_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[KEY_INDEX_W] = 0;
	else if (keycode == KEY_S)
		data->keys[KEY_INDEX_S] = 0;
	else if (keycode == KEY_A)
		data->keys[KEY_INDEX_A] = 0;
	else if (keycode == KEY_D)
		data->keys[KEY_INDEX_D] = 0;
	else if (keycode == KEY_Z)
		data->keys[KEY_INDEX_Z] = 0;
	else if (keycode == KEY_X)
		data->keys[KEY_INDEX_X] = 0;
	return (0);
}

static int	handle_zoom_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_NUMPAD_PLUS)
		data->keys[KEY_INDEX_PLUS] = 0;
	else if (keycode == KEY_MINUS)
		data->keys[KEY_INDEX_MINUS] = 0;
	return (0);
}
static int	handle_scale_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
		data->keys[KEY_INDEX_PGUP] = 0;
	else if (keycode == KEY_PGDOWN)
		data->keys[KEY_INDEX_PGDOWN] = 0;
	return (0);
}
static int	handle_shift_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->keys[KEY_INDEX_UP] = 0;
	else if (keycode == KEY_DOWN)
		data->keys[KEY_INDEX_DOWN] = 0;
	else if (keycode == KEY_LEFT)
		data->keys[KEY_INDEX_LEFT] = 0;
	else if (keycode == KEY_RIGHT)
		data->keys[KEY_INDEX_RIGHT] = 0;
	return (0);
}

int	handle_view_keyrelease(int key_code, t_data *data)
{
	handle_rotation_keyrelease(key_code, data);
	handle_zoom_keyrelease(key_code, data);
	handle_scale_keyrelease(key_code, data);
	handle_shift_keyrelease(key_code, data);
	return (1);
}