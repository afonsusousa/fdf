/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:32:12 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 23:32:06 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

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

void	project_axis_vector(double axis[3], int center[2], int end[2], t_view *view)
{
	double	coords[3];
	int		scale;

	scale = 30;
	coords[0] = axis[0] * scale;
	coords[1] = axis[1] * scale;
	coords[2] = axis[2] * scale;
	rotate_x_coords(coords, view->alpha);
	rotate_y_coords(coords, view->beta);
	rotate_z_coords(coords, view->gamma);
	end[0] = center[0] + (int)((coords[0] - coords[1]) * cos(view->angle));
	end[1] = center[1] + (int)((coords[0] + coords[1]) * sin(view->angle) - coords[2]);
}

void	draw_axis_border(t_data *img, int corner_x, int corner_y, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		draw_pixel_color(img, corner_x + i, corner_y, 0x444444, 1.0f);
		draw_pixel_color(img, corner_x + i, corner_y + size - 1, 0x444444, 1.0f);
		draw_pixel_color(img, corner_x, corner_y + i, 0x444444, 1.0f);
		draw_pixel_color(img, corner_x + size - 1, corner_y + i, 0x444444, 1.0f);
		i++;
	}
}

void	draw_axis_labels(t_data *img, int corner_x, int corner_y, int size)
{
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, 
		corner_y + 10, 0xFF0000, "X");
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, 
		corner_y + 25, 0x00FF00, "Y");
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, 
		corner_y + 40, 0x0000FF, "Z");
	if(img->view.top_down)
	mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, 
		corner_y + 55, 0x00FF00, "TOP_DOWN: YES");
	else 
		mlx_string_put(img->mlx, img->mlx_win, corner_x + size + 5, 
		corner_y + 55, 0xFF0000, "TOP_DOWN: NOPE");
}

void	get_axis_position(t_data *img, int *corner_x, int *corner_y, int *size)
{
	*size = img->menu_width / 3;
	*corner_x = img->menu_width / 3;
	*corner_y = 7 * (img->window_height / 9);
}
