/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_controls_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 02:20:35 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/27 02:32:05 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#ifdef AUDIO

void	display_effects_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 465, 0xFF8C7A, "EFFECTS:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 480, 0xFFFFFF,
		"4 - Ripple Effect");
	mlx_string_put(img->mlx, img->mlx_win, 15, 495, 0xFFFFFF, "5 - Wave X");
	mlx_string_put(img->mlx, img->mlx_win, 15, 510, 0xFFFFFF, "6 - Wave Y");
	mlx_string_put(img->mlx, img->mlx_win, 15, 525, 0xFFFFFF, "7 - DVD");
	mlx_string_put(img->mlx, img->mlx_win, 15, 540, 0xFFFFFF,
		"B/N - Bend/Unbend");
	mlx_string_put(img->mlx, img->mlx_win, 15, 555, 0xFFFFFF,
		"8 - Toggle Reactive Audio");
}

#else

void	display_effects_controls(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 10, 465, 0xFF8C7A, "EFFECTS:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 480, 0xFFFFFF,
		"4 - Ripple Effect");
	mlx_string_put(img->mlx, img->mlx_win, 15, 495, 0xFFFFFF, "5 - Wave X");
	mlx_string_put(img->mlx, img->mlx_win, 15, 510, 0xFFFFFF, "6 - Wave Y");
	mlx_string_put(img->mlx, img->mlx_win, 15, 525, 0xFFFFFF, "7 - DVD");
	mlx_string_put(img->mlx, img->mlx_win, 15, 540, 0xFFFFFF,
		"B/N - Bend/Unbend");
}

#endif