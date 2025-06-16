/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_priority_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:35:34 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/16 02:43:23 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "../../libft/libft.h"
#include <stdlib.h>

static bool	left_right_valid(t_line_info *l, t_line_info *r)
{
	if (!l || !r)
	{
		if (l)
			free(l);
		if (r)
			free(r);
		return (false);
	}
	return (true);
}

static void	merge_left(t_line_info arr[], t_line_info *l, t_line_info *r,
		int *indices)
{
	while (indices[0] < indices[3] && indices[1] < indices[4])
	{
		if (l[indices[0]].depth >= r[indices[1]].depth)
			arr[indices[2]++] = l[indices[0]++];
		else
			arr[indices[2]++] = r[indices[1]++];
	}
}

static void	merge_rest(t_line_info arr[], t_line_info *l, t_line_info *r,
		int *indices)
{
	while (indices[0] < indices[3])
		arr[indices[2]++] = l[indices[0]++];
	while (indices[1] < indices[4])
		arr[indices[2]++] = r[indices[1]++];
}

static void	merge(t_line_info arr[], int left, int mid, int right)
{
	int			n[2];
	int			i;
	t_line_info	*l;
	t_line_info	*r;
	int			indices[5];

	n[0] = mid - left + 1;
	n[1] = right - mid;
	l = malloc(n[0] * sizeof(t_line_info));
	r = malloc(n[1] * sizeof(t_line_info));
	if (!left_right_valid(l, r))
		return ;
	i = -1;
	while (++i < n[0])
		l[i] = arr[left + i];
	i = -1;
	while (++i < n[1])
		r[i] = arr[mid + 1 + i];
	ft_memset(&indices, 0, 2 * sizeof(int));
	indices[2] = left;
	indices[3] = n[0];
	indices[4] = n[1];
	merge_left(arr, l, r, indices);
	merge_rest(arr, l, r, indices);
	return (free(l), free(r));
}

void	merge_sort_lines(t_line_info arr[], int left, int right)
{
	int	mid;

	if (left < right)
	{
		mid = left + (right - left) / 2;
		merge_sort_lines(arr, left, mid);
		merge_sort_lines(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}
