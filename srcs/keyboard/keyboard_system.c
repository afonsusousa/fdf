/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 00:45:37 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

int	handle_exit_keys(t_data *data, int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}
void	reset_view(t_data *data)
{
	data->view.alpha = 0.0;
	data->view.beta = 0.0;
	data->view.gamma = 0.0;
	data->view.zoom = 15;
	data->view.scale = 1;
	data->view.offset_x = (data->window_width + data->menu_width) / 2;
	data->view.offset_y = data->window_height / 2;
	data->view.auto_rotate = 0;
	data->view.ripple.enabled = false;
	data->view.wave.enabled_x = false;
	data->view.wave.enabled_y = false;
	data->view.render_mode = RENDER_PRIORITY;
	data->view.view_mode = ISOMETRIC;
}

int	handle_reset_keys(int keycode, t_data *data)
{
	if (keycode == KEY_R)
	{
		reset_view(data);
		return (1);
	}
	return (0);
}

int	handle_rendering_keys(int keycode, t_data *data)
{
	if (keycode == KEY_M)
	{
		data->view.render_mode = (data->view.render_mode + 1) % 3;
		return (1);
	}
	else if (keycode == KEY_O)
	{
		data->view.alpha = 0.0;
		data->view.beta = 0.0;
		data->view.gamma = 0.0;
		ortographic_projection(data);
		return (1);
	}
	return (0);
}

int	handle_effects_keys(int keycode, t_data *data)
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
