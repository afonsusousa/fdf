/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:07:52 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../keyboard_bonus.h"

int	handle_scale_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
		data->keys[KEY_INDEX_PGUP] = true;
	else if (keycode == KEY_PGDOWN)
		data->keys[KEY_INDEX_PGDOWN] = true;
	else
		return (0);
	return (1);
}

int	handle_scale_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
		data->keys[KEY_INDEX_PGUP] = false;
	else if (keycode == KEY_PGDOWN)
		data->keys[KEY_INDEX_PGDOWN] = false;
	return (0);
}

void	smooth_scale(t_data *data)
{
	if (data->keys[KEY_INDEX_PGUP])
	{
		data->view.scale += SCALE_STEP;
		if (data->view.scale > 5.0)
			data->view.scale = 5.0;
	}
	if (data->keys[KEY_INDEX_PGDOWN])
	{
		data->view.scale -= SCALE_STEP;
		if (data->view.scale < 0.05)
			data->view.scale = 0.05;
	}
}
