/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:56:24 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 19:43:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void rotate_x_coords(double *y, double *z, double alpha)
{
	double cos_a = cos(alpha);
	double sin_a = sin(alpha);
	double temp_y = *y;
	double temp_z = *z;
	
	*y = temp_y * cos_a - temp_z * sin_a;
	*z = temp_y * sin_a + temp_z * cos_a;
}

void rotate_y_coords(double *x, double *z, double beta)
{
	double cos_b = cos(beta);
	double sin_b = sin(beta);
	double temp_x = *x;
	double temp_z = *z;
	
	*x = temp_x * cos_b + temp_z * sin_b;
	*z = -temp_x * sin_b + temp_z * cos_b;
}

void rotate_z_coords(double *x, double *y, double gamma)
{
	double cos_g = cos(gamma);
	double sin_g = sin(gamma);
	double temp_x = *x;
	double temp_y = *y;
	
	*x = temp_x * cos_g - temp_y * sin_g;
	*y = temp_x * sin_g + temp_y * cos_g;
}

void apply_projection(t_coords *coords, double x, double y, double z)
{
	coords->x = (int)((x - y) * cos(0.523599));
	coords->y = (int)((x + y) * sin(0.523599) - z);
}

void rotate_point(t_point *source, t_rotation *rotation)
{
	double x = (double)source->x;
	double y = (double)source->y;
	double z = (double)source->z;
	rotate_x_coords(&y, &z, rotation->alpha);
	rotate_y_coords(&x, &z, rotation->beta);
	rotate_z_coords(&x, &y, rotation->gamma);
	x *= rotation->scale;
	y *= rotation->scale;
	z *= rotation->scale;
	apply_projection(&source->display, x, y, z);
}