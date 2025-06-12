/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:16:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/12 03:25:32 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard_defines.h"

int	handle_keypress(int keycode, t_data *data)
{
	handle_exit_keys(keycode);
	handle_rotation_keys(keycode, data);  // Don't return early for rotation keys
	if (handle_zoom_keys(keycode, data))
		return (0);
	if (handle_scale_keys(keycode, data))
		return (0);
	if (handle_offset_keys(keycode, data))
		return (0);
	if (handle_reset_keys(keycode, data))
		return (0);
	if (handle_rendering_keys(keycode, data))
		return (0);
	if (handle_auto_rotation_keys(keycode, data))
		return (0);
	return (0);
}

