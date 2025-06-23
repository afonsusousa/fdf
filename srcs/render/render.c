/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:33:08 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/23 01:28:26 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_image(t_data *data)
{
	int	background_color;

	(void)data;
	background_color = 0x1a1a2e;
	draw_background(data, background_color);
}

static void	update_times(t_data *data)
{
	static const double	frame_duration = FRAME_DURATION;

	if (data->view.ripple.enabled)
		data->view.ripple.time += frame_duration;
	if (data->view.wave.enabled_x)
		data->view.wave.x_time += frame_duration;
	if (data->view.wave.enabled_y)
		data->view.wave.y_time += frame_duration;
}

int	rotate_and_render(t_data *data)
{
	clear_image(data);
	if (data->view.dvd)
		dvd(data);
	apply_keys(data);
	normalize_angles(data);
	update_times(data);
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