/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:00:00 by asousa            #+#    #+#             */
/*   Updated: 2025/06/17 18:14:16 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"
#include "../../../libft/libft.h"

void	set_rotation_status_strings(t_data *img, char **x_status,
		char **y_status, char **z_status)
{
	if (img->view.auto_rotate & 4)
		*x_status = "ON";
	else
		*x_status = "OFF";
	if (img->view.auto_rotate & 2)
		*y_status = "ON";
	else
		*y_status = "OFF";
	if (img->view.auto_rotate & 1)
		*z_status = "ON";
	else
		*z_status = "OFF";
}

void	build_rotation_status_text(char *auto_rotation_status,
		char *x_status, char *y_status, char *z_status)
{
	ft_strlcpy(auto_rotation_status, "Auto-Rotation: X:", 256);
	ft_strlcat(auto_rotation_status, x_status, 256);
	ft_strlcat(auto_rotation_status, " Y:", 256);
	ft_strlcat(auto_rotation_status, y_status, 256);
	ft_strlcat(auto_rotation_status, " Z:", 256);
	ft_strlcat(auto_rotation_status, z_status, 256);
}

void	build_effects_string(t_data *img, char *effects)
{
	effects[0] = '\0';
	if (img->view.ripple.enabled)
	{
		ft_strlcat(effects, " + ", 128 * (ft_strlen(effects) != 0));
		ft_strlcat(effects, "RIPPLE", 128);
	}
	if (img->view.wave.enabled_x)
	{
		ft_strlcat(effects, " + ", 128 * (ft_strlen(effects) != 0));
		ft_strlcat(effects, "WAVE-X", 128);
	}
	if (img->view.wave.enabled_y)
	{
		ft_strlcat(effects, " + ", 128 * (ft_strlen(effects) != 0));
		ft_strlcat(effects, "WAVE-Y", 128);
	}
	if (img->view.dvd)
	{
		ft_strlcat(effects, " + ", 128 * (ft_strlen(effects) != 0));
		ft_strlcat(effects, "DVD", 128);
	}
}

void	display_all_menu_info(t_data *img)
{
	display_rotation_info(img);
	display_view_info(img);
	display_auto_rotation_status(img);
	display_render_mode(img);
	display_effects_status(img);
	mlx_string_put(img->mlx, img->mlx_win, 10, 115, 0xFF8C7A, "Controls:");
}

void	display_all_controls(t_data *img)
{
	display_basic_controls(img);
	display_mouse_controls(img);
	display_rendering_controls(img);
	display_auto_rotation_controls(img);
	display_effects_controls(img);
	mlx_string_put(img->mlx, img->mlx_win, 10, 535, 0xFF8C7A, "SYSTEM:");
	mlx_string_put(img->mlx, img->mlx_win, 15, 550, 0xFFFFFF, "R - Reset View");
	mlx_string_put(img->mlx, img->mlx_win, 15, 565, 0xFFFFFF, "Q - Quit");
}
