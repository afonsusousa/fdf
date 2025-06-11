/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/11 00:39:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "../../minilibx-linux/mlx.h"

void	display_basic_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 20, 120, 0xFFFFFF, 
		"WASD-Rotate, ZX-Roll, +/-Zoom, PgUp/PgDn-Scale");
	mlx_string_put(img->mlx, img->mlx_win, 20, 135, 0xFFFFFF, 
		"Arrows-Move, R-Reset, Q-Quit");
}

void	display_mouse_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 20, 155, 0xFFFFFF,
		"Mouse: L-Rotate, R-Pan, Scroll-Zoom");
}

void	display_rendering_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 20, 175, 0xFFFFFF, 
		"P-Toggle Priority Rendering");
}

void	display_auto_rotation_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 20, 195, 0xFFFFFF, 
		"1/2/3-Toggle X/Y/Z Auto-Rot, 0-Chaos Mode");
}

void	display_all_controls(t_data *img)
{
	display_basic_controls(img);
	display_mouse_controls(img);
	display_rendering_controls(img);
	display_auto_rotation_controls(img);
}
