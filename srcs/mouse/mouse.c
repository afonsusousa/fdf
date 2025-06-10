/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:24:29 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 19:32:55 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

// Mouse button codes for Linux X11
#define MOUSE_LEFT_BUTTON	1
#define MOUSE_RIGHT_BUTTON	3
#define MOUSE_SCROLL_UP		4
#define MOUSE_SCROLL_DOWN	5

// Mouse event handlers
int handle_mouse_press(int button, int x, int y, t_data *data)
{
	data->mouse.is_pressed = 1;
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	data->mouse.button = button;
	return (0);
}

int handle_mouse_release(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	data->mouse.is_pressed = 0;
	return (0);
}

int handle_mouse_move(int x, int y, t_data *data)
{
	int delta_x;
	int delta_y;
	double sensitivity;
	
	if (!data->mouse.is_pressed)
		return (0);
	
	delta_x = x - data->mouse.last_x;
	delta_y = y - data->mouse.last_y;
	sensitivity = 0.005;
	
	if (data->mouse.button == MOUSE_LEFT_BUTTON)
	{
		// Left mouse button: rotate around X and Y axes
		// Invert Y axis for more intuitive control (drag up = rotate up)
		data->view.beta += delta_x * sensitivity;
		data->view.alpha -= delta_y * sensitivity;  // Inverted for intuitive control
	}
	else if (data->mouse.button == MOUSE_RIGHT_BUTTON)
	{
		// Right mouse button: roll (Z axis) and zoom
		data->view.gamma += delta_x * sensitivity;
		// Invert zoom direction (drag up = zoom in, drag down = zoom out)
		data->view.zoom -= delta_y * 0.1;
		if (data->view.zoom < 1)
			data->view.zoom = 1;
		if (data->view.zoom > 100)
			data->view.zoom = 100;
	}
	
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	return (0);
}

int handle_mouse_scroll(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	
	if (button == MOUSE_SCROLL_UP)
	{
		data->view.zoom += 2;
		if (data->view.zoom > 100)
			data->view.zoom = 100;
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		data->view.zoom -= 2;
		if (data->view.zoom < 1)
			data->view.zoom = 1;
	}
	return (0);
}

