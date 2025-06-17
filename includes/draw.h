/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 03:24:20 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "types.h"

// Line drawing
void	swap(int *a, int *b);
void	calculate_pixel_values(t_line *line, t_pixel_values *pixels);
int		get_interpolated_color(t_line *line, int x);
void	draw_steep(t_data *data, t_line *line);
void	draw_nonsteep(t_data *data, t_line *line);
void	draw_line_screen_only(t_data *data, t_point *p0, t_point *p1);
void	draw_line_with_offset(t_data *data, t_point *p0, t_point *p1);
void	init_line_struct(t_line *line, int p0[2], int p1[2]);
void	init_line(t_data *data, t_line *line, t_point *p0, t_point *p1);
void	draw_background(t_data *data, int color);
void	draw_menu_background(t_data *data, int color);

// Line priority and depth sorting
float	calculate_line_depth(t_line_info *line, t_view *view);
int		compare_depth(const void *a, const void *b);
void	draw_lines_priority(t_data *data);
void	add_line_data(t_line_info *line, t_point *p0, t_point *p1);
int		collect_horizontal_lines(t_data *data, t_line_info *lines);
int		collect_vertical_lines(t_data *data, t_line_info *lines, int start);
int		collect_lines(t_data *data, t_line_info *lines);

// Line traversal (logic-based rendering)
void	draw_lines_traversal(t_data *data);

// Colors
int		get_color_from_z(t_data *data, t_point *point);
int		interpolate_color(int color1, int color2, float t);
void	draw_pixel_color(t_data *data, int x, int y, t_color *color);

#endif
