/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_smooth_effects.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:52:04 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/18 21:38:53 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keyboard.h"

void smooth_bend(t_data *data)
{
	if (data->keys[KEY_INDEX_B])
	{
		data->view.range += data->view.rg_step;
		if (data->view.range > 0.1)
			data->view.range = 0.1;
	}
	if (data->keys[KEY_INDEX_N])
	{
		data->view.range -= data->view.rg_step;
		if (data->view.range < 0.0001)
			data->view.range = 0.0001;
	}
}