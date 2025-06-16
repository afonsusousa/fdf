/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 02:59:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include "../../../minilibx-linux/mlx.h"

void	display_basic_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 140, 0xFF8C7A, "MOVEMENT:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 155, 0xFFFFFF,
		"W/A/S/D - Rotate");
	mlx_string_put(img->mlx, img->mlx_win, 15, 170, 0xFFFFFF, "Z/X - Roll");
	mlx_string_put(img->mlx, img->mlx_win, 15, 185, 0xFFFFFF, "Arrows - Move");
	mlx_string_put(img->mlx, img->mlx_win, 15, 200, 0xFFFFFF, "+/- - Zoom");
	mlx_string_put(img->mlx, img->mlx_win, 15, 215, 0xFFFFFF,
		"PgUp/PgDn - Scale");
}

void	display_mouse_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 240, 0xFF8C7A, "MOUSE:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 255, 0xFFFFFF,
		"Left Click - Rotate");
	mlx_string_put(img->mlx, img->mlx_win, 15, 270, 0xFFFFFF, "Scroll - Zoom");
}

void	display_rendering_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 295, 0xFF8C7A, "RENDERING:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 310, 0xFFFFFF,
		"P - Priority Mode");
	mlx_string_put(img->mlx, img->mlx_win, 15, 325, 0xFFFFFF,
		"M - Render Mode");
	mlx_string_put(img->mlx, img->mlx_win, 15, 340, 0xFFFFFF,
		"O - Orthographic");
}

void	display_auto_rotation_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 365, 0xFF8C7A, "AUTO ROTATION:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 380, 0xFFFFFF,
		"1 - Toggle X Axis");
	mlx_string_put(img->mlx, img->mlx_win, 15, 395, 0xFFFFFF,
		"2 - Toggle Y Axis");
	mlx_string_put(img->mlx, img->mlx_win, 15, 410, 0xFFFFFF,
		"3 - Toggle Z Axis");
	mlx_string_put(img->mlx, img->mlx_win, 15, 425, 0xFFFFFF, "0 - Chaos Mode");
}

void	display_effects_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 450, 0xFF8C7A, "EFFECTS:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 465, 0xFFFFFF,
		"4 - Ripple Effect");
	mlx_string_put(img->mlx, img->mlx_win, 15, 480, 0xFFFFFF, "5 - Wave X");
	mlx_string_put(img->mlx, img->mlx_win, 15, 495, 0xFFFFFF, "6 - Wave Y");
}

void	display_all_controls(t_data *img)
{
	display_basic_controls(img);
	display_mouse_controls(img);
	display_rendering_controls(img);
	display_auto_rotation_controls(img);
	display_effects_controls(img);
	mlx_string_put(img->mlx, img->mlx_win, 10, 520, 0xFF8C7A, "SYSTEM:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 535, 0xFFFFFF, "R - Reset View");
	mlx_string_put(img->mlx, img->mlx_win, 15, 550, 0xFFFFFF, "Q - Quit");
}
