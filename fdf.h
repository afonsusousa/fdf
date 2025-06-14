/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:39:51 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "minilibx-linux/mlx.h"

// Include modular headers
#include "includes/types.h"
#include "includes/map.h"
#include "includes/draw.h"
#include "includes/transform.h"
#include "includes/controls.h"
#include "includes/menu.h"
#include "includes/utils.h"

// Main functions
int rotate_and_render(t_data *img);
void init_view(t_data *data);

#endif