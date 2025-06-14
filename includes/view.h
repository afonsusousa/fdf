/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:46:38 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 17:23:32 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

#include "../fdf.h"

// Orthographic projection views
void set_orthographic_view(t_data *data, int view_type);
void handle_orthographic_rotation(t_data *data, int key_index);
void ortographic_projection(t_data *data);

#endif