/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:37:51 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/26 04:06:39 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../keyboard.h"

static int	handle_wave_keys(int keycode, t_data *data)
{
	if (keycode == KEY_4)
	{
		data->view.ripple.enabled = !data->view.ripple.enabled;
		data->view.ripple.time = 0.0;
		return (1);
	}
	if (keycode == KEY_5)
	{
		data->view.wave.enabled_x = !data->view.wave.enabled_x;
		data->view.wave.x_time = 0.0;
		return (1);
	}
	if (keycode == KEY_6)
	{
		data->view.wave.enabled_y = !data->view.wave.enabled_y;
		data->view.wave.y_time = 0.0;
		return (1);
	}
	return (0);
}

int	handle_effects_keys(int keycode, t_data *data)
{
	if (handle_wave_keys(keycode, data))
		return (1);
	if (keycode == KEY_7)
	{
		data->view.dvd = !data->view.dvd;
		return (1);
	}
	if (keycode == KEY_8)
	{
		toggle_audio_reactive(data);
		data->time = 0;
		return (1);
	}
	return (0);
}
