/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_auto.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 19:34:22 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

static void	toggle_auto_rotate_x(t_data *data)
{
	data->view.auto_rotate ^= 4;
	if (data->view.auto_rotate & 8)
		data->view.auto_rotate ^= 8;
}

static void	toggle_auto_rotate_y(t_data *data)
{
	data->view.auto_rotate ^= 2;
	if (data->view.auto_rotate & 8)
		data->view.auto_rotate ^= 8;
}

static void	toggle_auto_rotate_z(t_data *data)
{
	data->view.auto_rotate ^= 1;
	if (data->view.auto_rotate & 8)
		data->view.auto_rotate ^= 8;
}

static void	toggle_chaos_mode(t_data *data)
{
	if (data->view.auto_rotate == 8)
		data->view.auto_rotate = 0;
	else
		data->view.auto_rotate = 8;
}

int	handle_auto_rotation_keys(int keycode, t_data *data)
{
	if (keycode == KEY_1)
		toggle_auto_rotate_x(data);
	else if (keycode == KEY_2)
		toggle_auto_rotate_y(data);
	else if (keycode == KEY_3)
		toggle_auto_rotate_z(data);
	else if (keycode == KEY_0)
		toggle_chaos_mode(data);
	else
		return (0);
	return (1);
}
