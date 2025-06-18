/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 00:42:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "types.h"

// Keyboard controls
void	keyboard_init(t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_keyrelease(int keycode, t_data *data);
void	auto_rotation(t_data *data);
void	apply_smooth_keys(t_data *data);
void	discrete_rotation(t_data *data);

// Keyboard helper functions
int		handle_effects_keys(int keycode, t_data *data);
int		handle_exit_keys(t_data *data, int keycode);
int		handle_reset_keys(int keycode, t_data *data);
int		handle_rendering_keys(int keycode, t_data *data);
int		handle_auto_rotation_keys(int keycode, t_data *data);
void	reset_view(t_data *data);

// Window event handlers
int		handle_close_button(t_data *data);

// Mouse controls
int		handle_mouse_press(int button, int x, int y, t_data *data);
int		handle_mouse_release(int button, int x, int y, t_data *data);
int		handle_mouse_move(int x, int y, t_data *data);
int		handle_mouse_scroll(int button, int x, int y, t_data *data);
void	init_mouse(t_data *data);

#endif
