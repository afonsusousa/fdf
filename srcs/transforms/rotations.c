/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:28:22 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:40:28 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <math.h>

void rotate_x_coords(double coords[3], double alpha)
{
	double cos_a;
	double sin_a;
	double temp_y;
	double temp_z;
	
	cos_a = cos(alpha);
	sin_a = sin(alpha);
	temp_y = coords[1];
	temp_z = coords[2];
	coords[1] = temp_y * cos_a - temp_z * sin_a;
	coords[2] = temp_y * sin_a + temp_z * cos_a;
}

void rotate_y_coords(double coords[3], double beta)
{
	double cos_b;
	double sin_b;
	double temp_x;
	double temp_z;
	
	cos_b = cos(beta);
	sin_b = sin(beta);
	temp_x = coords[0];
	temp_z = coords[2];
	coords[0] = temp_x * cos_b + temp_z * sin_b;
	coords[2] = -temp_x * sin_b + temp_z * cos_b;
}

void rotate_z_coords(double coords[3], double gamma)
{
	double cos_g;
	double sin_g;
	double temp_x;
	double temp_y;
	
	cos_g = cos(gamma);
	sin_g = sin(gamma);
	temp_x = coords[0];
	temp_y = coords[1];
	coords[0] = temp_x * cos_g - temp_y * sin_g;
	coords[1] = temp_x * sin_g + temp_y * cos_g;
}

