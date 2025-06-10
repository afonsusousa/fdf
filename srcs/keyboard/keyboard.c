/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:16:18 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 19:53:56 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include <stdlib.h>
#include <stdio.h>

void apply_auto_rotation(t_data *data)
{
	double auto_rotation_speed = 0.02;
	
	if (data->view.chaos_mode)
	{
		data->view.alpha += auto_rotation_speed * 1.3;
		data->view.beta += auto_rotation_speed * 1.1;
		data->view.gamma += auto_rotation_speed * 1.3;
	}
	else
	{
		if (data->view.auto_rotate_x)
			data->view.alpha += auto_rotation_speed;
		if (data->view.auto_rotate_y)
			data->view.beta += auto_rotation_speed;
		if (data->view.auto_rotate_z)
			data->view.gamma += auto_rotation_speed;
	}
}

// Key codes for Linux X11
#define KEY_ESC		65307
#define KEY_Q		113
#define KEY_W		119
#define KEY_A		97
#define KEY_S		115
#define KEY_D		100
#define KEY_Z		122
#define KEY_X		120
#define KEY_C		99
#define KEY_R		114
#define KEY_P		112
#define KEY_PLUS	61      // = key (plus with shift)
#define KEY_EQUAL	61      // = key without shift
#define KEY_NUMPAD_PLUS	65451   // Numpad plus
#define KEY_MINUS	45
#define KEY_1		49
#define KEY_2		50
#define KEY_3		51
#define KEY_0		48

int handle_keypress(int keycode, t_data *data)
{
	double rotation_step = 0.1;
	
	// Debug: Print keycode (can be removed later)
	printf("Key pressed: %d\n", keycode);
	
	// Exit controls
	if (keycode == KEY_ESC || keycode == KEY_Q)
		exit(0);
	
	// Rotation controls
	if (keycode == KEY_W)  // Rotate up (decrease alpha)
		data->view.alpha -= rotation_step;
	else if (keycode == KEY_S)  // Rotate down (increase alpha)
		data->view.alpha += rotation_step;
	else if (keycode == KEY_A)  // Rotate left (decrease beta)
		data->view.beta -= rotation_step;
	else if (keycode == KEY_D)  // Rotate right (increase beta)
		data->view.beta += rotation_step;
	else if (keycode == KEY_Z)  // Roll left (decrease gamma)
		data->view.gamma -= rotation_step;
	else if (keycode == KEY_X)  // Roll right (increase gamma)
		data->view.gamma += rotation_step;
	
	
	// Zoom controls
	else if (keycode == KEY_PLUS || keycode == KEY_EQUAL || keycode == KEY_NUMPAD_PLUS)  // Zoom in
	{
		data->view.zoom += 2;
		if (data->view.zoom > 100)
			data->view.zoom = 100;
	}
	else if (keycode == KEY_MINUS)  // Zoom out
	{
		data->view.zoom -= 2;
		if (data->view.zoom < 1)
			data->view.zoom = 1;
	}
	
	// Reset view
	else if (keycode == KEY_R)
	{
		data->view.alpha = 0.0;
		data->view.beta = 0.0;
		data->view.gamma = 0.0;
		data->view.zoom = 15;
		data->view.auto_rotate_x = false;
		data->view.auto_rotate_y = false;
		data->view.auto_rotate_z = false;
		data->view.chaos_mode = false;
	}
	
	// Toggle priority rendering
	else if (keycode == KEY_P)
	{
		data->view.priority_rendering = !data->view.priority_rendering;
	}
	
	// Auto-rotation toggles
	else if (keycode == KEY_1)  // Toggle X-axis auto-rotation
	{
		data->view.auto_rotate_x = !data->view.auto_rotate_x;
		if (data->view.auto_rotate_x && data->view.chaos_mode)
			data->view.chaos_mode = false;
	}
	else if (keycode == KEY_2)  // Toggle Y-axis auto-rotation
	{
		data->view.auto_rotate_y = !data->view.auto_rotate_y;
		if (data->view.auto_rotate_y && data->view.chaos_mode)
			data->view.chaos_mode = false;
	}
	else if (keycode == KEY_3)  // Toggle Z-axis auto-rotation
	{
		data->view.auto_rotate_z = !data->view.auto_rotate_z;
		if (data->view.auto_rotate_z && data->view.chaos_mode)
			data->view.chaos_mode = false;
	}
	else if (keycode == KEY_0)  // Toggle chaos mode (all axes)
	{
		data->view.chaos_mode = !data->view.chaos_mode;
		if (data->view.chaos_mode)
		{
			data->view.auto_rotate_x = false;
			data->view.auto_rotate_y = false;
			data->view.auto_rotate_z = false;
		}
	}
	
	return (0);
}

