/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:07:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../keyboard_bonus.h"

int	handle_zoom_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_NUMPAD_PLUS
		|| keycode == KEY_EQUAL)
		data->keys[KEY_INDEX_PLUS] = true;
	else if (keycode == KEY_MINUS)
		data->keys[KEY_INDEX_MINUS] = true;
	else
		return (0);
	return (1);
}

int	handle_zoom_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_PLUS || keycode == KEY_NUMPAD_PLUS
		|| keycode == KEY_EQUAL)
		data->keys[KEY_INDEX_PLUS] = false;
	else if (keycode == KEY_MINUS)
		data->keys[KEY_INDEX_MINUS] = false;
	return (0);
}

void	smooth_zoom(t_data *data)
{
	if (data->keys[KEY_INDEX_PLUS])
	{
		data->view.zoom += ZOOM_STEP;
		if (data->view.zoom > 75)
			data->view.zoom = 75;
	}
	if (data->keys[KEY_INDEX_MINUS])
	{
		data->view.zoom -= ZOOM_STEP;
		if (data->view.zoom < 4)
			data->view.zoom = 4;
	}
}
