/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_discrete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:44:37 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 17:48:20 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "./keyboard.h"

static void	discrete_rotation(t_data *data)
{
	static int last_key_state[6] = {0, 0, 0, 0, 0, 0};
	if (data->keys[KEY_INDEX_W] && !last_key_state[0])
		handle_orthographic_rotation(data, 0);
	if (data->keys[KEY_INDEX_S] && !last_key_state[1])
		handle_orthographic_rotation(data, 1);
	if (data->keys[KEY_INDEX_A] && !last_key_state[2])
		handle_orthographic_rotation(data, 2);
	if (data->keys[KEY_INDEX_D] && !last_key_state[3])
		handle_orthographic_rotation(data, 3);
	if (data->keys[KEY_INDEX_Z] && !last_key_state[4])
		handle_orthographic_rotation(data, 4);
	if (data->keys[KEY_INDEX_X] && !last_key_state[5])
		handle_orthographic_rotation(data, 5);
	last_key_state[0] = data->keys[KEY_INDEX_W];
	last_key_state[1] = data->keys[KEY_INDEX_S];
	last_key_state[2] = data->keys[KEY_INDEX_A];
	last_key_state[3] = data->keys[KEY_INDEX_D];
	last_key_state[4] = data->keys[KEY_INDEX_Z];
	last_key_state[5] = data->keys[KEY_INDEX_X];
}