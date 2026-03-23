/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:16:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 19:58:52 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	keyboard_init(t_data *data)
{
	ft_memset(data->keys, 0, 16);
}

int	handle_keypress(int keycode, t_data *data)
{
	handle_exit_keys(data, keycode);
	return (0);
}

int	handle_close_button(t_data *data)
{
	free_data(data);
	return (0);
}

int	handle_exit_keys(t_data *data, int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}
