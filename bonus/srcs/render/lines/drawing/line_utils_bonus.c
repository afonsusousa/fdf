/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:00:00 by asousa            #+#    #+#             */
/*   Updated: 2025/07/11 17:47:19 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	calculate_pixel_values(t_line *line, t_pixel_values *pixels)
{
	pixels->y_pixel = integer_of(line->current_y);
	pixels->y_fract = fractional_of(line->current_y);
	pixels->y_rfract = reverse_fractional_of(line->current_y);
}

int	get_interpolated_color(t_line *line, int x)
{
	int				range;

	range = line->x_end - line->x_start;
	if (range == 0)
		return (interpolate_color(line->color1, line->color2, 0));
	else
	{
		return (interpolate_color(line->color1, line->color2, 
				(unsigned char)((255 * (x - line->x_start)) / range)));
	}
}
