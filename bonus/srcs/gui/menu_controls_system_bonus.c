/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_controls_system_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 02:22:45 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#ifdef AUDIO

void	display_all_controls(t_data *img)
{
	display_basic_controls(img);
	display_mouse_controls(img);
	display_rendering_controls(img);
	display_auto_rotation_controls(img);
	display_effects_controls(img);
	mlx_string_put(img->mlx, img->mlx_win, 10, 580, 0xFF8C7A, "SYSTEM:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 595, 0xFFFFFF, "R - Reset View");
	mlx_string_put(img->mlx, img->mlx_win, 15, 610, 0xFFFFFF, "Q - Quit");
}
#else

void	display_all_controls(t_data *img)
{
	display_basic_controls(img);
	display_mouse_controls(img);
	display_rendering_controls(img);
	display_auto_rotation_controls(img);
	display_effects_controls(img);
	mlx_string_put(img->mlx, img->mlx_win, 10, 570, 0xFF8C7A, "SYSTEM:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 585, 0xFFFFFF, "R - Reset View");
	mlx_string_put(img->mlx, img->mlx_win, 15, 600, 0xFFFFFF, "Q - Quit");
}

#endif