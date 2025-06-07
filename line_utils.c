/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:06:32 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/07 19:50:17 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int integer_of(float n)
{
	return ((int)n);
}
int round_of(float n)
{
	return (integer_of(n + 0.5));
}
int fractional_of(float n)
{
	if (n > 0)
		return (n - integer_of(n));
	return (n - integer_of(n) + 1);
}

int reverse_fractional_of(float n)
{
	return (1 - fractional_of(n));
}