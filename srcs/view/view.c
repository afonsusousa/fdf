/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:28:03 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 16:42:14 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void init_view(t_data *data)
{
	data->view.alpha = 0;     
	data->view.beta = 0;      
	data->view.gamma = 0;    
	data->view.scale = 0.25;    
	data->view.axis[0] = 0.0;
	data->view.axis[1] = 0.0;
	data->view.axis[2] = 1.0;
	data->view.zoom = 15;
	data->view.angle = 0.523599;
	data->view.render_mode = RENDER_PRIORITY;
	data->view.view_mode = ISOMETRIC;
	data->view.auto_rotate = 0; 
	data->view.offset_x = (data->window_width + data->menu_width) / 2;
	data->view.offset_y = data->window_height/2;
	data->view.ripple = false;
	data->view.wave_x = false;
	data->view.wave_y = false;
}
