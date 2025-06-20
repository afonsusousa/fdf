/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:07:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 18:08:02 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../keyboard.h"
#include "fdf.h"

int	handle_zoom_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_NUMPAD_PLUS)
		data->keys[KEY_INDEX_PLUS] = 1;
	else if (keycode == KEY_MINUS)
		data->keys[KEY_INDEX_MINUS] = 1;
	else
		return (0);
	return (1);
}

int	handle_zoom_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_NUMPAD_PLUS)
		data->keys[KEY_INDEX_PLUS] = 0;
	else if (keycode == KEY_MINUS)
		data->keys[KEY_INDEX_MINUS] = 0;
	return (0);
}

void	smooth_zoom(t_data *data)
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
