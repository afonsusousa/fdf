/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:32:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 00:21:10 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_axis_line(t_data *img, int start[2], int end[2], int color)
{
	int		steps;
	int		i;
	float	increment[2];
	float	pos[2];
	t_color	pixel_color;

	pixel_color.hex = color;
	pixel_color.rgba.a = 255;
	calculate_line_params(start, end, &steps, increment);
	pos[0] = start[0];
	pos[1] = start[1];
	i = -1;
	while (++i <= steps)
	{
		if (pos[0] >= 0 && pos[0] < img->w_width && pos[1] >= 0
			&& pos[1] < img->w_height)
		{
			draw_pixel_color(img, (int)pos[0], (int)pos[1], &pixel_color);
		}
		pos[0] += increment[0];
		pos[1] += increment[1];
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
	int		x;
	int		y;
	t_color	pixel_color;

	pixel_color.hex = 0xFFFFFF;
	pixel_color.rgba.a = 255;
	y = 0;
	while (y < size)
	{
		x = -1;
		while (++x < size)
		{
			draw_pixel_color(img, corner_x + x, corner_y + y, &pixel_color);
		}
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
}

void	get_axis_position(t_data *img, int *corner_x, int *corner_y, int *size)
{
	*size = img->m_width / 3;
	*corner_x = img->m_width / 3;
	*corner_y = 7 * (img->w_height / 9);
}
