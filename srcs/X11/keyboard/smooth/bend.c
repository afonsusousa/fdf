/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bend.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:08:20 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 02:19:55 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../keyboard.h"

int handle_bend_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_B)
		data->keys[KEY_INDEX_B] = 1;
	else if (keycode == KEY_N)
		data->keys[KEY_INDEX_N] = 1;
	else
		return (0);
	return (1);
}

int handle_bend_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_B)
		data->keys[KEY_INDEX_B] = 0;
	else if (keycode == KEY_N)
		data->keys[KEY_INDEX_N] = 0;
	return (0);
}

void smooth_bend(t_data *data)
{
	if (data->keys[KEY_INDEX_B])
	{
		data->view.bend = true;
		data->view.brange += data->view.rg_step;
		if (data->view.brange > 0.1)
			data->view.brange = 0.1;
	}
	if (data->keys[KEY_INDEX_N])
	{
		data->view.brange -= data->view.rg_step;
		if (data->view.brange < 0.0001)
		{
			data->view.brange = 0.0001;
			data->view.bend = false;
		}
	}
}
