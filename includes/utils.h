/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/17 00:32:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// Float utilities
int		integer_of(float n);
int		round_of(float n);
float	float_of(float n);
float	fractional_of(float n);
float	reverse_fractional_of(float n);

// merge_sort
bool	merge_sort_lines(t_line_info arr[], int low, int high);

#endif
