/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 01:58:44 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

int	handle_exit_keys(int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
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
	data->view.auto_rotate_x = false;
	data->view.auto_rotate_y = false;
	data->view.auto_rotate_z = false;
	data->view.chaos_mode = false;
	data->view.ripple = false;
	data->view.render_mode = RENDER_PRIORITY;
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
	if (keycode == KEY_P)
	{
		data->view.brainfuck_priority = !data->view.brainfuck_priority;
		return (1);
	}
	else if (keycode == KEY_M)
	{
		data->view.render_mode = (data->view.render_mode + 1) % 2;
		return (1);
	}
	return (0);
}

int handle_effects_keys(int keycode, t_data *data)
{
	if (keycode == KEY_4)
	{
		data->view.ripple = !data->view.ripple;
		return (1);
	}
	return (0);
}
