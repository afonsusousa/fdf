/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:06:33 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 18:07:52 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../keyboard.h"
#include "fdf.h"

int	handle_shift_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->keys[KEY_INDEX_UP] = true;
	else if (keycode == KEY_DOWN)
		data->keys[KEY_INDEX_DOWN] = true;
	else if (keycode == KEY_LEFT)
		data->keys[KEY_INDEX_LEFT] = true;
	else if (keycode == KEY_RIGHT)
		data->keys[KEY_INDEX_RIGHT] = true;
	else
		return (0);
	return (1);
}

int	handle_shift_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->keys[KEY_INDEX_UP] = false;
	else if (keycode == KEY_DOWN)
		data->keys[KEY_INDEX_DOWN] = false;
	else if (keycode == KEY_LEFT)
		data->keys[KEY_INDEX_LEFT] = false;
	else if (keycode == KEY_RIGHT)
		data->keys[KEY_INDEX_RIGHT] = false;
	return (0);
}

void	smooth_shift(t_data *data)
{
	if (data->keys[KEY_INDEX_UP])
	{
		data->view.off_y -= (int)(SHIFT_STEP * log10(data->view.zoom));
		if (data->view.off_y < 0)
			data->view.off_y = 0;
	}
	if (data->keys[KEY_INDEX_DOWN])
	{
		data->view.off_y += (int)(SHIFT_STEP * log10(data->view.zoom));
		if (data->view.off_y > data->w_height)
			data->view.off_y = data->w_height;
	}
	if (data->keys[KEY_INDEX_LEFT])
	{
		data->view.off_x -= (int)(SHIFT_STEP * log10(data->view.zoom));
		if (data->view.off_x < data->m_width + 1)
			data->view.off_x = data->m_width + 1;
	}
	if (data->keys[KEY_INDEX_RIGHT])
	{
		data->view.off_x += (int)(SHIFT_STEP * log10(data->view.zoom));
		if (data->view.off_x > data->w_width)
			data->view.off_x = data->w_width;
	}
}
