/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 20:20:22 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "../../minilibx-linux/mlx.h"
#include <stdio.h>


void	display_rotation_info(t_data *img)
{
	char	rotation_text[256];

	sprintf(rotation_text, "Gamma: %.3f  Alpha: %.3f  Beta: %.3f", 
		img->view.gamma, img->view.alpha, img->view.beta);
	mlx_string_put(img->mlx, img->mlx_win, 20, 30, 0xFFFFFF, rotation_text);
}

void	display_view_info(t_data *img)
{
	char	view_text[256];
	char	*priority_status;

	if (img->view.priority_rendering)
		priority_status = "ON";
	else
		priority_status = "OFF";
	sprintf(view_text, "Scale: %.2f  Zoom: %d  Priority: %s", 
		img->view.scale, img->view.zoom, priority_status);
	mlx_string_put(img->mlx, img->mlx_win, 20, 50, 0xFFFFFF, view_text);
}

void	display_auto_rotation_status(t_data *img)
{
	char	auto_rotation_status[256];
	char	*x_status;
	char	*y_status;
	char	*z_status;

	if (img->view.chaos_mode)
		sprintf(auto_rotation_status, "Auto-Rotation: CHAOS MODE");
	else
	{
		if (img->view.auto_rotate_x)
			x_status = "ON";
		else
			x_status = "OFF";
		if (img->view.auto_rotate_y)
			y_status = "ON";
		else
			y_status = "OFF";
		if (img->view.auto_rotate_z)
			z_status = "ON";
		else
			z_status = "OFF";
		sprintf(auto_rotation_status, "Auto-Rotation: X:%s Y:%s Z:%s", 
			x_status, y_status, z_status);
	}
	mlx_string_put(img->mlx, img->mlx_win, 20, 70, 0xFFFFFF, 
		auto_rotation_status);
}

void	display_menu_header(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 20, 100, 0xAAAAAAA, "Controls:");
}

void	display_all_menu_info(t_data *img)
{
	display_rotation_info(img);
	display_view_info(img);
	display_auto_rotation_status(img);
	display_menu_header(img);
}
