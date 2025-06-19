/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/19 00:50:59 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "../../fdf.h"

# define KEY_ESC		65307
# define KEY_Q			113
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_Z			122
# define KEY_X			120
# define KEY_R			114
# define KEY_P			112
# define KEY_M			109
# define KEY_O			111
# define KEY_B			98
# define KEY_N			110
# define KEY_PLUS		43
# define KEY_EQUAL		61
# define KEY_NUMPAD_PLUS	65451
# define KEY_MINUS		45
# define KEY_1			49
# define KEY_2			50
# define KEY_3			51
# define KEY_4			52
# define KEY_5			53
# define KEY_6			54
# define KEY_7			55
# define KEY_0			48
# define KEY_UP			65362
# define KEY_DOWN		65364
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_PGUP		65365
# define KEY_PGDOWN		65366

# define KEY_INDEX_W 0
# define KEY_INDEX_S 1
# define KEY_INDEX_A 2
# define KEY_INDEX_D 3
# define KEY_INDEX_Z 4
# define KEY_INDEX_X 5
# define KEY_INDEX_PLUS 6
# define KEY_INDEX_MINUS 7
# define KEY_INDEX_B 8
# define KEY_INDEX_N 9
# define KEY_INDEX_PGUP 10
# define KEY_INDEX_PGDOWN 11
# define KEY_INDEX_UP 12
# define KEY_INDEX_DOWN 13
# define KEY_INDEX_LEFT 14
# define KEY_INDEX_RIGHT 15

// Function declarations

// Discrete action handlers
int		handle_exit_keys(t_data *data, int keycode);
int		handle_reset_keys(int keycode, t_data *data);
int		handle_rendering_keys(int keycode, t_data *data);
int		handle_effects_keys(int keycode, t_data *data);
int		handle_auto_rotation_keys(int keycode, t_data *data);
void	reset_view(t_data *data);

// Smooth motion handlers - keypress
int		handle_rotation_keypress(int keycode, t_data *data);
int		handle_shift_keypress(int keycode, t_data *data);
int		handle_zoom_keypress(int keycode, t_data *data);
int		handle_scale_keypress(int keycode, t_data *data);
int		handle_bend_keypress(int keycode, t_data *data);

// Smooth motion handlers - keyrelease
int		handle_rotation_keyrelease(int keycode, t_data *data);
int		handle_shift_keyrelease(int keycode, t_data *data);
int		handle_zoom_keyrelease(int keycode, t_data *data);
int		handle_scale_keyrelease(int keycode, t_data *data);
int		handle_bend_keyrelease(int keycode, t_data *data);

// Smooth motion application functions
void	smooth_rotation(t_data *data);
void	smooth_shift(t_data *data);
void	smooth_zoom(t_data *data);
void	smooth_scale(t_data *data);
void	smooth_bend(t_data *data);
void	auto_rotation(t_data *data);

// Discrete rotation functions
void	discrete_rotation(t_data *data);

// Window handlers
int		handle_close_button(t_data *data);

#endif
