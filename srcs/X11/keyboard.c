/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:16:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 00:58:46 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

void	keyboard_init(t_data *data)
{
	ft_memset(data->keys, 0, 16);
}

int	handle_keypress(int keycode, t_data *data)
{
	handle_exit_keys(data, keycode);
	handle_rotation_keypress(keycode, data);
	handle_shift_keypress(keycode, data);
	handle_zoom_keypress(keycode, data);
	handle_scale_keypress(keycode, data);
	handle_bend_keypress(keycode, data);
	if (handle_effects_keys(keycode, data))
		return (0);
	if (handle_reset_keys(keycode, data))
		return (0);
	if (handle_rendering_keys(keycode, data))
		return (0);
	if (handle_auto_rotation_keys(keycode, data))
		return (0);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	handle_rotation_keyrelease(keycode, data);
	handle_shift_keyrelease(keycode, data);
	handle_zoom_keyrelease(keycode, data);
	handle_scale_keyrelease(keycode, data);
	handle_bend_keyrelease(keycode, data);
	return (0);
}

void	apply_keys(t_data *data)
{
	smooth_zoom(data);
	smooth_shift(data);
	if (data->view.view_mode == ORTOGRAPHIC)
		return (discrete_rotation(data));
	smooth_rotation(data);
	smooth_scale(data);
	smooth_bend(data);
	if (data->view.view_mode == ISOMETRIC)
		auto_rotation(data);
}
