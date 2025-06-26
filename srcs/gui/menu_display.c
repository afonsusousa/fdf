/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/26 20:38:56 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_rotation_info(t_data *data)
{
	char	rotation_text[256];
	char *strs[3];

	strs[0] = ft_itoa((int)(data->view.gamma * 180.0 / M_PI));
	strs[1] = ft_itoa((int)(data->view.alpha * 180.0 / M_PI));
	strs[2] = ft_itoa((int)(data->view.beta * 180.0 / M_PI));
	if (!strs[0] || !strs[1] || !strs[2])
		return (free_strs(strs, 3), free_data(data));
	ft_strlcpy(rotation_text, "Gamma: ", sizeof(rotation_text));
	ft_strlcat(rotation_text, strs[0], sizeof(rotation_text));
	ft_strlcat(rotation_text, "'  Alpha: ", sizeof(rotation_text));
	ft_strlcat(rotation_text, strs[1], sizeof(rotation_text));
	ft_strlcat(rotation_text, "'  Beta: ", sizeof(rotation_text));
	ft_strlcat(rotation_text, strs[2], sizeof(rotation_text));
	ft_strlcat(rotation_text, "'", sizeof(rotation_text));
	mlx_string_put(data->mlx, data->mlx_win, 15, 30, 0xFFFFFF, rotation_text);
	free(strs[0]);
	free(strs[1]);
	free(strs[2]);
}

void	display_view_info(t_data *data)
{
	char	view_text[256];
	char	*strs[2];
	int		scale_percent;

	scale_percent = (int)(data->view.scale * 100);
	strs[0] = ft_itoa(data->view.zoom);
	strs[1] = ft_itoa(scale_percent);
	if (!strs[0] || !strs[1])
		return (free_strs(strs, 2), free_data(data));
	ft_strlcpy(view_text, "Scale: ", sizeof(view_text));
	ft_strlcat(view_text, strs[0], sizeof(view_text));
	ft_strlcat(view_text, "%  Zoom: ", sizeof(view_text));
	ft_strlcat(view_text, strs[1], sizeof(view_text));
	mlx_string_put(data->mlx, data->mlx_win, 15, 45, 0xFFFFFF, view_text);
	free(strs[0]);
	free(strs[1]);
}

void	display_auto_rotation_status(t_data *data)
{
	char	auto_rotation_status[256];
	char	*x_status;
	char	*y_status;
	char	*z_status;

	if (data->view.auto_rotate == 8)
	{
		ft_strlcpy(auto_rotation_status, "Auto-Rotation: CHAOS MODE",
			sizeof(auto_rotation_status));
	}
	else
	{
		set_rotation_status_strings(data, &x_status, &y_status, &z_status);
		build_rotation_status_text(auto_rotation_status, x_status, y_status,
			z_status);
	}
	mlx_string_put(data->mlx, data->mlx_win, 15, 60, 0xFFFFFF,
		auto_rotation_status);
}

void	display_render_mode(t_data *data)
{
	char	render_text[256];
	char	*mode_name;

	if (data->view.render_mode == RENDER_PRIORITY)
		mode_name = "PRIORITY";
	else if (data->view.render_mode == RENDER_BRAINFUCK_PRIORITY)
		mode_name = "BRAINF#(K PRIORITY";
	else if (data->view.render_mode == RENDER_TRAVERSAL)
		mode_name = "TRAVERSAL";
	else
		mode_name = "UNKNOWN";
	ft_strlcpy(render_text, "Render Mode: ", sizeof(render_text));
	ft_strlcat(render_text, mode_name, sizeof(render_text));
	mlx_string_put(data->mlx, data->mlx_win, 15, 75, 0xFFFFFF, render_text);
}

void	display_effects_status(t_data *data)
{
	char	effects_text[256];
	char	active_effects[128];
	char	view_mode_text[256];
	char	*mode_name;

	build_effects_string(data, active_effects);
	ft_strlcpy(effects_text, "Effects: ", sizeof(effects_text));
	ft_strlcat(effects_text, active_effects, sizeof(effects_text));
	mlx_string_put(data->mlx, data->mlx_win, 15, 90, 0xFFFFFF, effects_text);
	if (data->view.view_mode == ISOMETRIC)
		mode_name = "ISOMETRIC";
	else if (data->view.view_mode == ORTOGRAPHIC)
		mode_name = "ORTHOGRAPHIC";
	else if (data->view.view_mode == SPHERICAL)
		mode_name = "SPHERICAL";
	else
		mode_name = "UNKNOWN";
	ft_strlcpy(view_mode_text, "View Mode: ", sizeof(view_mode_text));
	ft_strlcat(view_mode_text, mode_name, sizeof(view_mode_text));
	mlx_string_put(data->mlx, data->mlx_win, 15, 105, 0xFFFFFF, view_mode_text);
}
