/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_smooth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:04:14 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 18:44:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

static void	smooth_rotation(t_data *data)
{
	if (data->keys[KEY_INDEX_W])
		data->view.alpha += data->view.rotation_step;
	if (data->keys[KEY_INDEX_S])
		data->view.alpha -= data->view.rotation_step;
	if (data->keys[KEY_INDEX_A])
		data->view.beta -= data->view.rotation_step;
	if (data->keys[KEY_INDEX_D])
		data->view.beta += data->view.rotation_step;
	if (data->keys[KEY_INDEX_Z])
		data->view.gamma -= data->view.rotation_step;
	if (data->keys[KEY_INDEX_X])
		data->view.gamma += data->view.rotation_step;
}

static void	smooth_zoom(t_data *data)
{
	if (data->keys[KEY_INDEX_PLUS])
	{
		data->view.zoom += data->view.zoom_step;
		if (data->view.zoom > 75)
			data->view.zoom = 75;
	}
	if (data->keys[KEY_INDEX_MINUS])
	{
		data->view.zoom -= data->view.zoom_step;
		if (data->view.zoom < 5)
			data->view.zoom = 5;
	}
}

static void	smooth_scale(t_data *data)
{
	if (data->keys[KEY_INDEX_PGUP])
	{
		data->view.scale += data->view.scale_step;
		if (data->view.scale > 5.0)
			data->view.scale = 5.0;
	}
	if (data->keys[KEY_INDEX_PGDOWN])
	{
		data->view.scale -= data->view.scale_step;
		if (data->view.scale < 0.05)
			data->view.scale = 0.05;
	}
}

static void	smooth_shift(t_data *data)
{
	if (data->keys[KEY_INDEX_UP])
	{
		data->view.offset_y -= data->view.shift_step;
		if (data->view.offset_y < 0)
			data->view.offset_y = 0;
	}
	if (data->keys[KEY_INDEX_DOWN])
	{
		data->view.offset_y += data->view.shift_step;
		if (data->view.offset_y > data->window_height)
			data->view.offset_y = data->window_height;
	}
	if (data->keys[KEY_INDEX_LEFT])
	{
		data->view.offset_x -= data->view.shift_step;
		if (data->view.offset_x < data->menu_width + 1)
			data->view.offset_x = data->menu_width + 1;
	}
	if (data->keys[KEY_INDEX_RIGHT])
	{
		data->view.offset_x += data->view.shift_step;
		if (data->view.offset_x > data->window_width)
			data->view.offset_x = data->window_width;
	}
}

void	apply_keys(t_data *data)
{
	if (data->view.view_mode == ISOMETRIC)
		smooth_rotation(data);
	else if (data->view.view_mode == ORTOGRAPHIC)
		discrete_rotation(data);
	smooth_zoom(data);
	smooth_scale(data);
	smooth_shift(data);
}
