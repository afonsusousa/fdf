/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_read_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:28:28 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf_bonus.h"

static bool	is_valid(int c, int baselen)
{
	static const char	*lcbase = "0123456789abcdef";
	static const char	*ucbase = "0123456789ABCDEF";
	int					i;

	i = 0;
	while (i < baselen)
	{
		if (c == lcbase[i] || c == ucbase[i])
			return (1);
		i++;
	}
	return (0);
}

static bool	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	atoi_base(char *nptr)
{
	int	result;
	int	digit_value;

	result = 0;
	if (nptr && *nptr == '0' && (*(nptr + 1) == 'x' || *(nptr + 1) == 'X'))
		nptr += 2;
	while (is_valid(*nptr, 16))
	{
		if (*nptr >= '0' && *nptr <= '9')
			digit_value = *nptr - '0';
		else if (*nptr >= 'A' && *nptr <= 'F')
			digit_value = *nptr - 'A' + 10;
		else if (*nptr >= 'a' && *nptr <= 'f')
			digit_value = *nptr - 'a' + 10;
		else
			break ;
		result = result * 16 + digit_value;
		nptr++;
	}
	return (result);
}

void	point_atoi(t_point *point, char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	point->paint = false;
	point->color = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign *= -1;
	while (is_digit(*nptr))
		result = result * 10 + (*nptr++ - '0');
	point->z = result * sign;
	if (*nptr != ',')
		return ;
	nptr++;
	point->color = atoi_base(nptr);
	point->paint = true;
}
