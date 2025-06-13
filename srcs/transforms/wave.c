/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 03:27:25 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/13 03:56:21 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double wave_height(t_data *data, t_point *point)
{
	double k;
	double amplitude;
	double angular_freq;
	double distance;

	k = 0.8;
	amplitude = 1;
	angular_freq = 1;
	distance = 0;
	if (data->view.wave_x)
		distance = point->x;
	else if (data->view.wave_y)
		distance = point->y;
	return (amplitude 
		* sin((k * distance) - (angular_freq * data->time)));
}