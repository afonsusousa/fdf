/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 20:03:51 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include "../../../libft/libft.h"
#include "../../../minilibx-linux/mlx.h"
#include <stdio.h>

void	display_rotation_info(t_data *img)
{
	char	rotation_text[256];
	char	*gamma_str;
	char	*alpha_str;
	char	*beta_str;

	gamma_str = ft_itoa((int)(img->view.gamma * 180.0 / M_PI));
	alpha_str = ft_itoa((int)(img->view.alpha * 180.0 / M_PI));
	beta_str = ft_itoa((int)(img->view.beta * 180.0 / M_PI));
	ft_strlcpy(rotation_text, "Gamma: ", sizeof(rotation_text));
	ft_strlcat(rotation_text, gamma_str, sizeof(rotation_text));
	ft_strlcat(rotation_text, "'  Alpha: ", sizeof(rotation_text));
	ft_strlcat(rotation_text, alpha_str, sizeof(rotation_text));
	ft_strlcat(rotation_text, "'  Beta: ", sizeof(rotation_text));
	ft_strlcat(rotation_text, beta_str, sizeof(rotation_text));
	ft_strlcat(rotation_text, "'", sizeof(rotation_text));
	mlx_string_put(img->mlx, img->mlx_win, 15, 30, 0xFFFFFF, rotation_text);
	free(gamma_str);
	free(alpha_str);
	free(beta_str);
}

void	display_view_info(t_data *img)
{
	char	view_text[256];
	char	*zoom_str;
	char	*scale_str;
	int		scale_percent;

	scale_percent = (int)(img->view.scale * 100);
	zoom_str = ft_itoa(img->view.zoom);
	scale_str = ft_itoa(scale_percent);
	ft_strlcpy(view_text, "Scale: ", sizeof(view_text));
	ft_strlcat(view_text, scale_str, sizeof(view_text));
	ft_strlcat(view_text, "%  Zoom: ", sizeof(view_text));
	ft_strlcat(view_text, zoom_str, sizeof(view_text));
	mlx_string_put(img->mlx, img->mlx_win, 15, 45, 0xFFFFFF, view_text);
	free(zoom_str);
	free(scale_str);
}

void	display_auto_rotation_status(t_data *img)
{
	char	auto_rotation_status[256];
	char	*x_status;
	char	*y_status;
	char	*z_status;

	if (img->view.auto_rotate == 8)
	{
		ft_strlcpy(auto_rotation_status, "Auto-Rotation: CHAOS MODE",
			sizeof(auto_rotation_status));
	}
	else
	{
		set_rotation_status_strings(img, &x_status, &y_status, &z_status);
		build_rotation_status_text(auto_rotation_status, x_status,
			y_status, z_status);
	}
	mlx_string_put(img->mlx, img->mlx_win, 15, 60, 0xFFFFFF,
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
	ft_strlcpy(render_text, "Render Mode: ", sizeof(render_text));
	ft_strlcat(render_text, mode_name, sizeof(render_text));
	mlx_string_put(img->mlx, img->mlx_win, 15, 75, 0xFFFFFF, render_text);
}

void	display_effects_status(t_data *img)
{
	char	effects_text[256];
	char	active_effects[128];

	build_effects_string(img, active_effects);
	ft_strlcpy(effects_text, "Effects: ", sizeof(effects_text));
	ft_strlcat(effects_text, active_effects, sizeof(effects_text));
	mlx_string_put(img->mlx, img->mlx_win, 15, 90, 0xFFFFFF, effects_text);
}
