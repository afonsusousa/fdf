/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/10 18:27:29 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "types.h"

// Rotations
void	normalize_angles(t_data *data);
void	rotate_x_coords(double coords[3], double alpha);
void	rotate_y_coords(double coords[3], double beta);
void	rotate_z_coords(double coords[3], double gamma);
void	transform_point(t_data *data, t_point *source);
void	transform(t_data *data);
void	project(t_data *data, t_point *point);

// Effect transforms

void	init_ripple(t_data *data);
void	ripple(t_data *data, t_point *point);
void	init_wave(t_data *data);
void	wave(t_data *data, t_point *point);
void	dvd(t_data *data);
void	bend(t_data *data, t_point *point);

// Spherical projection
void	polarize_points(t_map *map);
void	spherize(t_point *point, t_data *data);
void	cylindrize(t_point *point, t_data *data);

#endif
