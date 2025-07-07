/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "../keyboard_bonus.h"

int	handle_exit_keys(t_data *data, int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}

int	handle_reset_keys(int keycode, t_data *data)
{
	if (keycode == KEY_R)
	{
		init_view(data);
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
	else if (keycode == KEY_I)
	{
		data->view.view_mode = ISOMETRIC;
		return (1);
	}
	else if (keycode == KEY_O)
	{
		data->view.view_mode = ORTOGRAPHIC;
		data->view.alpha = 0.0;
		data->view.beta = 0.0;
		data->view.gamma = 0.0;
		return (1);
	}
	else if (keycode == KEY_G)
	{
		data->view.view_mode = SPHERICAL;
		return (1);
	}
	return (0);
}
