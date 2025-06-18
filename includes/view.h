/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:38 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/18 20:06:23 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "../fdf.h"

// View initialization
void	init_view(t_data *data);
void	init_optimal_scale(t_data *data);

// Orthographic projection views
void	set_orthographic_view(t_data *data, int view_type);
void	handle_orthographic_rotation(t_data *data, int key_index);
void	ortographic_projection(t_data *data);

// Point
bool	in_screen(t_data *data, t_point *point);

#endif