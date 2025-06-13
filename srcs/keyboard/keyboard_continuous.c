/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_continuous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:04:14 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 02:54:26 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

static void	continuous_rotation(t_data *data)
{
	double	rotation_step;

	rotation_step = 0.01;
	if (data->keys[KEY_INDEX_W])
		data->view.alpha += rotation_step; 
	if (data->keys[KEY_INDEX_S])
		data->view.alpha -= rotation_step;
	if (data->keys[KEY_INDEX_A])
		data->view.beta -= rotation_step;
	if (data->keys[KEY_INDEX_D])
		data->view.beta += rotation_step;
	if (data->keys[KEY_INDEX_Z])
		data->view.gamma -= rotation_step;
	if (data->keys[KEY_INDEX_X])
		data->view.gamma += rotation_step;
}

static void	continuous_zoom(t_data *data)
{
	int zoom_step;

	zoom_step = 1;
	if (data->keys[KEY_INDEX_PLUS])
	{
		data->view.zoom += zoom_step;
		if(data->view.zoom > 75)
			data->view.zoom = 75;
	}
	if(data->keys[KEY_INDEX_MINUS])
	{
		data->view.zoom -= zoom_step;
		if(data->view.zoom < 5)
			data->view.zoom = 5;
	}
}

static void	continuous_scale(t_data *data)
{
	double scale_step;

	scale_step = 0.005;
	if (data->keys[KEY_INDEX_PGUP])
	{
		data->view.scale += scale_step;
		if (data->view.scale > 5.0)
			data->view.scale = 5.0;
	}
	if (data->keys[KEY_INDEX_PGDOWN])
	{
		data->view.scale -= scale_step;
		if (data->view.scale < 0.05)
			data->view.scale = 0.05;
	}
}

static void	continuous_shift(t_data *data)
{
	int shift_step;

	shift_step = 2;
	if (data->keys[KEY_INDEX_UP])
	{
		data->view.offset_y -= shift_step;
		if (data->view.offset_y < 0)
			data->view.offset_y = 0;
	}
	if (data->keys[KEY_INDEX_DOWN])
	{
		data->view.offset_y += shift_step;
		if (data->view.offset_y > data->window_height)
			data->view.offset_y = data->window_height;
	}
	if (data->keys[KEY_INDEX_LEFT])
	{
		data->view.offset_x -= shift_step;
		if (data->view.offset_x < data->menu_width + 1)
			data->view.offset_x = data->menu_width + 1;
	}
	if (data->keys[KEY_INDEX_RIGHT])
	{
		data->view.offset_x += shift_step;
		if (data->view.offset_x > data->window_width)
			data->view.offset_x = data->window_width;
	}
}

void apply_keys(t_data *data)
{
	continuous_rotation(data);
	continuous_zoom(data);
	continuous_scale(data);
	continuous_shift(data);
}

