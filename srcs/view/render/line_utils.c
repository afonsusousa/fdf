/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:00:00 by asousa            #+#    #+#             */
/*   Updated: 2025/06/16 20:15:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../fdf.h"

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	calculate_pixel_values(t_line *line, t_pixel_values *pixels)
{
	pixels->y_pixel = integer_of(line->intersectY);
	pixels->y_fract = fractional_of(line->intersectY);
	pixels->y_rfract = reverse_fractional_of(line->intersectY);
}

int	get_interpolated_color(t_line *line, int x)
{
	if ((line->xpxl2 - line->xpxl1) == 0)
		return (interpolate_color(line->color1, line->color2, 0.0f));
	else
		return (interpolate_color(line->color1, line->color2,
				(float)(x - line->xpxl1) / (float)(line->xpxl2
			- line->xpxl1)));
}
