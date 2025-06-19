/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:05:45 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 02:20:05 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../keyboard.h"

int	handle_rotation_keypress(int keycode, t_data *data)
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

int	handle_rotation_keyrelease(int keycode, t_data *data)
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

void	auto_rotation(t_data *data)
{
	if (data->view.auto_rotate == 8)
	{
		data->view.alpha += data->view.auto_rotation_speed * 1.3;
		data->view.beta += data->view.auto_rotation_speed * 1.1;
		data->view.gamma += data->view.auto_rotation_speed * 1.3;
	}
	else
	{
		if (data->view.auto_rotate & 4)
			data->view.alpha += data->view.auto_rotation_speed;
		if (data->view.auto_rotate & 2)
			data->view.beta += data->view.auto_rotation_speed;
		if (data->view.auto_rotate & 1)
			data->view.gamma += data->view.auto_rotation_speed;
	}
}

void	smooth_rotation(t_data *data)
{
	if (data->keys[KEY_INDEX_W])
		data->view.alpha += data->view.r_step;
	if (data->keys[KEY_INDEX_S])
		data->view.alpha -= data->view.r_step;
	if (data->keys[KEY_INDEX_A])
		data->view.beta -= data->view.r_step;
	if (data->keys[KEY_INDEX_D])
		data->view.beta += data->view.r_step;
	if (data->keys[KEY_INDEX_Z])
		data->view.gamma -= data->view.r_step;
	if (data->keys[KEY_INDEX_X])
		data->view.gamma += data->view.r_step;
}