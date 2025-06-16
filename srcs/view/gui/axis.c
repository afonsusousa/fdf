/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:32:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 18:21:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

void	draw_axis_line(t_data *img, int start[2], int end[2], int color)
{
	int		dx;
	int		dy;
	int		steps;
	int		i;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = end[0] - start[0];
	dy = end[1] - start[1];
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = (float)dx / steps;
	y_inc = (float)dy / steps;
	x = start[0];
	y = start[1];
	i = -1;
	while (++i <= steps)
	{
		if (x >= 0 && x < img->window_width && y >= 0 && y < img->window_height)
			draw_pixel_color(img, (int)x, (int)y, color, 1.0f);
		x += x_inc;
		y += y_inc;
	}
}

void	project_axis_vector(double axis[3], int center[2], int end[2],
		t_view *view)
{
	int	scale;

	scale = 30;
	view->axis[0] = axis[0] * scale;
	view->axis[1] = axis[1] * scale;
	view->axis[2] = axis[2] * scale;
	rotate_x_coords(view->axis, view->alpha);
	rotate_y_coords(view->axis, view->beta);
	rotate_z_coords(view->axis, view->gamma);
	end[0] = center[0] + (int)((view->axis[0] - view->axis[1])
			* cos(view->angle));
	end[1] = center[1] + (int)((view->axis[0] + view->axis[1])
			* sin(view->angle) - view->axis[2]);
}

void	draw_axis_border(t_data *img, int corner_x, int corner_y, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = -1;
		while (++x < size)
			draw_pixel_color(img, corner_x + x, corner_y + y, 0xFFFFFF, 1.0f);
		y++;
	}
}

void	draw_axis_labels(t_data *img, int corner_x, int corner_y, int size)
{
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y + 10,
		0xFF0000, "X");
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y + 25,
		0x00FF00, "Y");
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y + 40,
		0x0000FF, "Z");
	if (img->view.top_down)
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y
			+ 55, 0xFF0000, "TOP_DOWN: YES");
	else
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y
			+ 55, 0x00FF00, "TOP_DOWN: NOPE");
	if (img->view.left_tilt)
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y
			+ 70, 0xFF0000, "LEFT_TILT: YES");
	else
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y
			+ 70, 0x00FF00, "LEFT_TILT: NOPE");
	if (img->view.right_tilt)
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y
			+ 85, 0xFF0000, "RIGHT_TILT: YES");
	else
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, corner_y
			+ 85, 0x00FF00, "RIGHT_TILT: NOPE");
}

void	get_axis_position(t_data *img, int *corner_x, int *corner_y, int *size)
{
	*size = img->menu_width / 3;
	*corner_x = img->menu_width / 3;
	*corner_y = 7 * (img->window_height / 9);
}
