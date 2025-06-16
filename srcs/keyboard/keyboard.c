/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:16:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 02:29:51 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

int	handle_keypress(int keycode, t_data *data)
{
	handle_exit_keys(data, keycode);
	handle_view_keypress(keycode, data);
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
