/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:07:52 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 18:08:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../keyboard.h"
#include "fdf.h"

int	handle_scale_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
		data->keys[KEY_INDEX_PGUP] = 1;
	else if (keycode == KEY_PGDOWN)
		data->keys[KEY_INDEX_PGDOWN] = 1;
	else
		return (0);
	return (1);
}

int	handle_scale_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_PGUP)
		data->keys[KEY_INDEX_PGUP] = 0;
	else if (keycode == KEY_PGDOWN)
		data->keys[KEY_INDEX_PGDOWN] = 0;
	return (0);
}

void	smooth_scale(t_data *data)
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
