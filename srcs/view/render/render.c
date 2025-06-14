/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:33:08 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 18:22:29 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

static void clear_image(t_data *data)
{
	(void) data;
	int background_color = 0x1a1a2e; 
	draw_background(data, background_color);
}

int rotate_and_render(t_data *data)
{
    static const double frame_duration_60_fps = 1.0 / 60.0;

    data->time += frame_duration_60_fps;
	clear_image(data);
	if (data->view.view_mode == ISOMETRIC)
		apply_auto_rotation(data);
	apply_keys(data);
	normalize_angles(data);
	transform(data);
	if (data->view.render_mode != RENDER_TRAVERSAL)
		draw_lines_priority(data);   
	else 
		draw_lines_traversal(data);  
	draw_menu_background(data, 0x3a3544);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	display_complete_menu(data);
	return (0);
}