/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 22:02:40 by amagno-r         ###   ########.fr       */
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
void	x_transforms(t_data *data, t_point *point, double coords[3]);
void	y_transforms(t_data *data, t_point *point, double coords[3]);
void	z_transforms(t_data *data, t_point *point, double coords[3]);
void	transform_point(t_data *data, t_point *source);
void	rotate_vector(double vector[3], t_view *view);
void	transform(t_data *data);
void	project(t_data *data, t_point *point);

// Effect transforms

void	init_ripple(t_data *data);
double	apply_ripple(t_data *data, t_point *point);
void	init_wave(t_data *data);
double	apply_wave(t_data *data, t_point *point);
void	dvd(t_data *data);

#endif
