/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 21:40:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 00:38:25 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

void	project_and_draw_axis(t_data *img, int center[2], t_view *view,
		t_axis_params *params)
{
	project_axis_vector(params->axis, center, params->end, view);
	draw_axis_line(img, center, params->end, params->color);
}

void	draw_axis_vectors(t_data *img, int center[2], t_view *view)
{
	double			x_axis[3];
	double			y_axis[3];
	double			z_axis[3];
	t_axis_params	params;

	init_axis_vectors(x_axis, y_axis, z_axis);
	params.axis = x_axis;
	params.color = 0xFF0000;
	project_and_draw_axis(img, center, view, &params);
	params.axis = y_axis;
	params.color = 0x00FF00;
	project_and_draw_axis(img, center, view, &params);
	params.axis = z_axis;
	params.color = 0x0000FF;
	project_and_draw_axis(img, center, view, &params);
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

void	calculate_line_params(int start[2], int end[2], int *steps,
		float increment[2])
{
	int	delta[2];

	delta[0] = end[0] - start[0];
	delta[1] = end[1] - start[1];
	if (abs(delta[0]) > abs(delta[1]))
		*steps = abs(delta[0]);
	else
		*steps = abs(delta[1]);
	if (*steps > 0)
	{
		increment[0] = (float)delta[0] / *steps;
		increment[1] = (float)delta[1] / *steps;
	}
	else
	{
		increment[0] = 0;
		increment[1] = 0;
	}
}
