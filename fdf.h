/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 23:31:17 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 03:24:42 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// Include modular headers
# include "includes/controls.h"
# include "includes/draw.h"
# include "includes/map.h"
# include "includes/menu.h"
# include "includes/transform.h"
# include "includes/types.h"
# include "includes/utils.h"
# include "includes/view.h"

// Main functions
void	free_data(t_data *data);
void	free_and_null(t_line_info **address);
int		rotate_and_render(t_data *img);
void	init_view(t_data *data);

#endif