/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 20:12:11 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "../../minilibx-linux/mlx.h"

void	draw_menu_background(t_data *data, int color)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < data->window_height)
	{
		x = 0;
		while (x < data->menu_width)
			draw_pixel_color(data, x++, y, color, 1.0f);
		y++;
	}
}

void	display_complete_menu(t_data *img)
{
	display_all_menu_info(img);
	display_all_controls(img);
}
