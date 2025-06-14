/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:28:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:52:12 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void init_view(t_data *data)
{
	data->view.alpha = 67.809;     
	data->view.beta = 67.809;      
	data->view.gamma = 203.427;    
	data->view.scale = 0.25;    
	data->view.axis[0] = 0.0;
	data->view.axis[1] = 0.0;
	data->view.axis[2] = 1.0;
	data->view.zoom = 15;
	data->view.angle = 0.523599;
	data->view.render_mode = RENDER_PRIORITY;
	data->view.auto_rotate_x = false;
	data->view.auto_rotate_y = false;
	data->view.auto_rotate_z = false;
	data->view.chaos_mode = false;
	data->view.offset_x = (data->window_width + data->menu_width) / 2;
	data->view.offset_y = data->window_height/2;
	data->view.ripple = false;
	data->view.wave_x = false;
	data->view.wave_y = false;
}
