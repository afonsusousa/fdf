/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42port.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:38 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/22 20:51:02 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "../fdf.h"

# define ROTATION_STEP 0.01
# define ZOOM_STEP 1
# define SCALE_STEP 0.005
# define SHIFT_STEP 2
# define RANGE_STEP 0.0001
# define AUTO_ROTATION_SPEED 0.005

// 1 / 60 [60fps]
# define FRAME_DURATION 0.01666666

// View initialization
void	init_view(t_data *data);
void	init_optimal_scale(t_data *data);

// Orthographic projection views
void	set_orthographic_view(t_data *data, int view_type);
void	handle_orthographic_rotation(t_data *data, int key_index);

// Point
bool	in_screen(t_data *data, t_point *point);

#endif