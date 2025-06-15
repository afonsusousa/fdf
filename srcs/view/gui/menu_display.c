/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 20:07:08 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include "../../../minilibx-linux/mlx.h"
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

	sprintf(view_text, "Scale: %.2f  Zoom: %d", 
		img->view.scale, img->view.zoom);
	mlx_string_put(img->mlx, img->mlx_win, 20, 50, 0xFFFFFF, view_text);
}

void	display_auto_rotation_status(t_data *img)
{
	char	auto_rotation_status[256];
	char	*x_status;
	char	*y_status;
	char	*z_status;

	if (img->view.auto_rotate == 8)
		sprintf(auto_rotation_status, "Auto-Rotation: CHAOS MODE");
	else
	{
		if (img->view.auto_rotate & 4)
			x_status = "ON";
		else
			x_status = "OFF";
		if (img->view.auto_rotate & 2)
			y_status = "ON";
		else
			y_status = "OFF";
		if (img->view.auto_rotate & 1)
			z_status = "ON";
		else
			z_status = "OFF";
		sprintf(auto_rotation_status, "Auto-Rotation: X:%s Y:%s Z:%s", 
			x_status, y_status, z_status);
	}
	mlx_string_put(img->mlx, img->mlx_win, 20, 70, 0xFFFFFF, 
		auto_rotation_status);
}

void	display_render_mode(t_data *img)
{
	char	render_text[256];
	char	*mode_name;

	if (img->view.render_mode == RENDER_PRIORITY)
		mode_name = "PRIORITY";
	else if (img->view.render_mode == RENDER_BRAINFUCK_PRIORITY)
		mode_name = "BRAINF#(K PRIORITY";
	else if (img->view.render_mode == RENDER_TRAVERSAL)
		mode_name = "TRAVERSAL";
	else
		mode_name = "UNKNOWN";
	sprintf(render_text, "Render Mode: %s", mode_name);
	mlx_string_put(img->mlx, img->mlx_win, 20, 90, 0xFFFFFF, render_text);
}

void	display_menu_header(t_data *img)
{
	mlx_string_put(img->mlx, img->mlx_win, 20, 125, 0xAAAAAAA, "Controls:");
}

void	display_effects_status(t_data *img)
{
	char	effects_text[256];
	char	*effect_name;

	if (img->view.ripple.enabled)
		effect_name = "RIPPLE";
	else if (img->view.wave.enabled_x)
		effect_name = "WAVE-X";
	else if (img->view.wave.enabled_y)
		effect_name = "WAVE-Y";
	else
		effect_name = "NONE";
	sprintf(effects_text, "Effects: %s", effect_name);
	mlx_string_put(img->mlx, img->mlx_win, 20, 105, 0xFFFFFF, effects_text);
}

void	display_all_menu_info(t_data *img)
{
	display_rotation_info(img);
	display_view_info(img);
	display_auto_rotation_status(img);
	display_render_mode(img);
	display_effects_status(img);
	display_menu_header(img);
}
