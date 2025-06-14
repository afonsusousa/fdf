/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:32:10 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 15:40:24 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void init_line_struct(t_line *line, int p0[2], int p1[2])
{
    line->dx = p1[0] - p0[0];
    line->dy = p1[1] - p0[1];
    if (fabs(line->dx) < 0.001f)
    {
        if (line->dy > 0)
            line->gradient = 1000.0f;
        else
            line->gradient = -1000.0f;
    }
    else
        line->gradient = line->dy / line->dx;
    line->xpxl1 = p0[0];
    line->xpxl2 = p1[0];
    line->intersectY = (float)p0[1];
}

static bool prepare_line_endpoints(int start[2], int end[2], int z_values[2], bool *steep)
{
    bool swapped_for_x_order;

    swapped_for_x_order = false;
    *steep = abs(end[1] - start[1]) > abs(end[0] - start[0]);
    if (*steep)
    {
        swap(&start[0], &start[1]);
        swap(&end[0], &end[1]);
    }
    if (start[0] > end[0])
    {
        swap(&start[0], &end[0]);
        swap(&start[1], &end[1]);
        swap(&z_values[0], &z_values[1]);
        swapped_for_x_order = true;
    }
    return (swapped_for_x_order);
}

static void set_line_colors(t_line *line, t_point *p0, t_point *p1,
                            int z_values[2], bool swapped_for_x_order, t_map *map)
{
    line->color1 = get_color_from_z(z_values[0], map->min_z, map->max_z);
    line->color2 = get_color_from_z(z_values[1], map->min_z, map->max_z);
    if (p0->paint || p1->paint)
    {
        line->color1 = (p0->color * !swapped_for_x_order) + (p1->color * swapped_for_x_order);
        line->color2 = (p1->color * !swapped_for_x_order) + (p0->color * swapped_for_x_order);
    }
}

void init_line(t_data *data, t_line *line, t_point *p0, t_point *p1)
{
    bool swapped_for_x_order;
    int start[2];
    int end[2];
    int z_values[2];

    start[0] = p0->display[0] + data->view.offset_x;
    start[1] = p0->display[1] + data->view.offset_y;
    end[0] = p1->display[0] + data->view.offset_x;
    end[1] = p1->display[1] + data->view.offset_y;
    z_values[0] = p0->z;
    z_values[1] = p1->z;

    swapped_for_x_order = prepare_line_endpoints(start, end, z_values, &line->steep);
    init_line_struct(line, start, end);
    set_line_colors(line, p0, p1, z_values, swapped_for_x_order, data->map);
}