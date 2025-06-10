/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:40:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 21:09:04 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	init_axis_vectors(double x_axis[3], double y_axis[3], double z_axis[3])
{
	x_axis[0] = 1.0;
	x_axis[1] = 0.0;
	x_axis[2] = 0.0;
	y_axis[0] = 0.0;
	y_axis[1] = 1.0;
	y_axis[2] = 0.0;
	z_axis[0] = 0.0;
	z_axis[1] = 0.0;
	z_axis[2] = 1.0;
}

void	draw_axis_vectors(t_data *img, int center[2], t_view *view)
{
	int		x_end[2];
	int		y_end[2];
	int		z_end[2];
	double	x_axis[3];
	double	y_axis[3];
	double	z_axis[3];

	init_axis_vectors(x_axis, y_axis, z_axis);
	project_axis_vector(x_axis, center, x_end, view);
	project_axis_vector(y_axis, center, y_end, view);
	project_axis_vector(z_axis, center, z_end, view);
	draw_axis_line(img, center, x_end, 0xFF0000);
	draw_axis_line(img, center, y_end, 0x00FF00);
	draw_axis_line(img, center, z_end, 0x0000FF);
}

void	display_axis_info(t_data *img)
{
	int	corner_x;
	int	corner_y;
	int	size;
	int	center[2];

	get_axis_position(img, &corner_x, &corner_y, &size);
	center[0] = corner_x + size / 2;
	center[1] = corner_y + size / 2;
	draw_axis_border(img, corner_x, corner_y, size);
	draw_axis_vectors(img, center, &img->view);
	draw_axis_labels(img, corner_x, corner_y, size);
}
