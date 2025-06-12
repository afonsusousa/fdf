/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:55:45 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/12 17:16:45 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../../libft/libft.h"
#include "keyboard.h"

void keyboard_init(t_data *data)
{
	data->keys[KEY_INDEX_W] = 0;
	data->keys[KEY_INDEX_S] = 0;
	data->keys[KEY_INDEX_A] = 0;
	data->keys[KEY_INDEX_D] = 0;
	data->keys[KEY_INDEX_Z] = 0;
	data->keys[KEY_INDEX_X] = 0;
	data->keys[KEY_INDEX_PLUS] = 0;
	data->keys[KEY_INDEX_MINUS] = 0; 
	data->keys[KEY_INDEX_PGUP] = 0;
	data->keys[KEY_INDEX_PGDOWN] = 0;
	data->keys[KEY_INDEX_UP] = 0;
	data->keys[KEY_INDEX_DOWN] = 0;
	data->keys[KEY_INDEX_LEFT] = 0;
	data->keys[KEY_INDEX_RIGHT] = 0;
}

