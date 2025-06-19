/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 18:22:22 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "types.h"

// Menu display functions
void	display_rotation_info(t_data *img);
void	display_view_info(t_data *img);
void	display_auto_rotation_status(t_data *img);
void	display_render_mode(t_data *img);
void	display_view_mode(t_data *img);
void	display_effects_status(t_data *img);
void	display_all_menu_info(t_data *img);

// Menu display helper functions
void	set_rotation_status_strings(t_data *img, char **x_status,
			char **y_status, char **z_status);
void	build_rotation_status_text(char *auto_rotation_status, char *x_status,
			char *y_status, char *z_status);
void	build_effects_string(t_data *img, char *active_effects);
void	display_all_menu_info(t_data *img);
void	display_all_controls(t_data *img);

// Menu controls display
void	display_basic_controls(t_data *img);
void	display_mouse_controls(t_data *img);
void	display_rendering_controls(t_data *img);
void	display_auto_rotation_controls(t_data *img);
void	display_effects_controls(t_data *img);
void	display_all_controls(t_data *img);

// Main menu function
void	display_complete_menu(t_data *img);

// Axis display
void	display_axis_info(t_data *img);
void	draw_axis_line(t_data *img, int start[2], int end[2], int color);
void	project_axis_vector(double axis[3], int center[2], int end[2],
			t_view *view);
void	draw_axis_border(t_data *img, int corner_x, int corner_y, int size);
void	draw_axis_labels(t_data *img, int corner_x, int corner_y, int size);
void	get_axis_position(t_data *img, int *corner_x, int *corner_y, int *size);
void	init_axis_vectors(double x_axis[3], double y_axis[3], double z_axis[3]);
void	draw_axis_vectors(t_data *img, int center[2], t_view *view);
void	calculate_line_params(int start[2], int end[2], int *steps,
			float increment[2]);

#endif
