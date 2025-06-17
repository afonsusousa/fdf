/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_smooth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:04:14 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 18:22:21 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

static void	smooth_rotation(t_data *data)
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

static void	smooth_zoom(t_data *data)
{
	if (data->keys[KEY_INDEX_PLUS])
	{
		data->view.zoom += data->view.z_step;
		if (data->view.zoom > 75)
			data->view.zoom = 75;
	}
	if (data->keys[KEY_INDEX_MINUS])
	{
		data->view.zoom -= data->view.z_step;
		if (data->view.zoom < 4)
			data->view.zoom = 4;
	}
}

static void	smooth_scale(t_data *data)
{
	if (data->keys[KEY_INDEX_PGUP])
	{
		data->view.scale += data->view.sc_step;
		if (data->view.scale > 5.0)
			data->view.scale = 5.0;
	}
	if (data->keys[KEY_INDEX_PGDOWN])
	{
		data->view.scale -= data->view.sc_step;
		if (data->view.scale < 0.05)
			data->view.scale = 0.05;
	}
}

static void	smooth_shift(t_data *data)
{
	if (data->keys[KEY_INDEX_UP])
	{
		data->view.off_y -= (int)(data->view.sh_step * log10(data->view.zoom));
		if (data->view.off_y < 0)
			data->view.off_y = 0;
	}
	if (data->keys[KEY_INDEX_DOWN])
	{
		data->view.off_y += (int)(data->view.sh_step * log10(data->view.zoom));
		if (data->view.off_y > data->w_height)
			data->view.off_y = data->w_height;
	}
	if (data->keys[KEY_INDEX_LEFT])
	{
		data->view.off_x -= (int)(data->view.sh_step * log10(data->view.zoom));
		if (data->view.off_x < data->m_width + 1)
			data->view.off_x = data->m_width + 1;
	}
	if (data->keys[KEY_INDEX_RIGHT])
	{
		data->view.off_x += (int)(data->view.sh_step * log10(data->view.zoom));
		if (data->view.off_x > data->w_width)
			data->view.off_x = data->w_width;
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
