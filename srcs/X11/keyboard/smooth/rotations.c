/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:05:45 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 18:07:12 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../keyboard.h"
#include "fdf.h"

int	handle_rotation_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[KEY_INDEX_W] = true;
	else if (keycode == KEY_S)
		data->keys[KEY_INDEX_S] = true;
	else if (keycode == KEY_A)
		data->keys[KEY_INDEX_A] = true;
	else if (keycode == KEY_D)
		data->keys[KEY_INDEX_D] = true;
	else if (keycode == KEY_Z)
		data->keys[KEY_INDEX_Z] = true;
	else if (keycode == KEY_X)
		data->keys[KEY_INDEX_X] = true;
	else
		return (0);
	return (1);
}

int	handle_rotation_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[KEY_INDEX_W] = false;
	else if (keycode == KEY_S)
		data->keys[KEY_INDEX_S] = false;
	else if (keycode == KEY_A)
		data->keys[KEY_INDEX_A] = false;
	else if (keycode == KEY_D)
		data->keys[KEY_INDEX_D] = false;
	else if (keycode == KEY_Z)
		data->keys[KEY_INDEX_Z] = false;
	else if (keycode == KEY_X)
		data->keys[KEY_INDEX_X] = false;
	return (0);
}

void	auto_rotation(t_data *data)
{
	if (data->view.auto_rotate == 8)
	{
		data->view.alpha += AUTO_ROTATION_SPEED * 1.3;
		data->view.beta += AUTO_ROTATION_SPEED * 1.1;
		data->view.gamma += AUTO_ROTATION_SPEED * 1.3;
	}
	else
	{
		if (data->view.auto_rotate & 4)
			data->view.alpha += AUTO_ROTATION_SPEED;
		if (data->view.auto_rotate & 2)
			data->view.beta += AUTO_ROTATION_SPEED;
		if (data->view.auto_rotate & 1)
			data->view.gamma += AUTO_ROTATION_SPEED;
	}
}

void	smooth_rotation(t_data *data)
{
	if (data->keys[KEY_INDEX_W])
		data->view.alpha += AUTO_ROTATION_SPEED;
	if (data->keys[KEY_INDEX_S])
		data->view.alpha -= AUTO_ROTATION_SPEED;
	if (data->keys[KEY_INDEX_A])
		data->view.beta -= AUTO_ROTATION_SPEED;
	if (data->keys[KEY_INDEX_D])
		data->view.beta += AUTO_ROTATION_SPEED;
	if (data->keys[KEY_INDEX_Z])
		data->view.gamma -= AUTO_ROTATION_SPEED;
	if (data->keys[KEY_INDEX_X])
		data->view.gamma += AUTO_ROTATION_SPEED;
}
