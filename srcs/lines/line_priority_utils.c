/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_priority_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:35:34 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/15 16:50:54 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

static void     array_swap(t_line_info *a, t_line_info *b)
{
        t_line_info     t;

        t = *a;
        *a = *b;
        *b = t;
}

static int      partition(t_line_info arr[], int low, int high)
{
        t_line_info     pivot;
        int     i;
        int     j;

        pivot = arr[high];
        i = low - 1;
        j = low;
        while (j <= high - 1)
        {
            if (arr[j].depth >= pivot.depth)
                array_swap(&arr[++i], &arr[j]);
            j++;
        }
        array_swap(&arr[i + 1], &arr[high]);
        return (i + 1);
}

void    quick_sort_lines(t_line_info arr[], int low, int high)
{
        int     pi;

        if (low < high)
        {
                pi = partition(arr, low, high);
                quick_sort_lines(arr, low, pi - 1);
                quick_sort_lines(arr, pi + 1, high);
        }
}