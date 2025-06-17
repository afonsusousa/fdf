/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 18:38:09 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "types.h"

// Map initialization
void	point_atoi(t_point *point, char *nptr);
void	init_map(t_data *data, char *file_name);
void	map_set_limits(t_data *data);
void	print_map(t_data *data);
int		count_map_width(char **row);
void	get_map_dimensions(t_data *data, int map_file);
void	parse_map_row(t_data *data, char **row, int y);
void	read_map_data(t_data *data, int map_file);
void	colorize_points(t_data *data);

// Point operations
void	init_point(t_point *point, int x, int y, char *value);
void	center_coordinates(t_data *data);
t_point	*get_point(t_data *data, int x, int y);

#endif
