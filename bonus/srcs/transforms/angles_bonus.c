/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:48:25 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	normalize_angle(double *angle)
{
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
	while (*angle < 0)
		*angle += 2 * M_PI;
}

void	normalize_angles(t_data *data)
{
	normalize_angle(&data->view.alpha);
	normalize_angle(&data->view.beta);
	normalize_angle(&data->view.gamma);
}
