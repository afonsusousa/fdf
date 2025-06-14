/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:24:29 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/14 01:36:00 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#define MOUSE_LEFT_BUTTON	1
#define MOUSE_RIGHT_BUTTON	3
#define MOUSE_SCROLL_UP		4
#define MOUSE_SCROLL_DOWN	5

int handle_mouse_press(int button, int x, int y, t_data *data)
{
	if (x < data->menu_width)
		return (0);
	
	data->mouse.is_pressed = 1;
	data->mouse.last_x = x - data->menu_width;
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
	int wireframe_x;
	int wireframe_y;
	int delta_x;
	int delta_y;
	double rotation_sensitivity;
	double pan_sensitivity;
	
	if (!data->mouse.is_pressed)
		return (0);
	if (x < data->menu_width)
	{
		data->mouse.is_pressed = 0; 
		return (0);
	}
	wireframe_x = x - data->menu_width;
	wireframe_y = y;
	delta_x = wireframe_x - data->mouse.last_x;
	delta_y = wireframe_y - data->mouse.last_y;
	rotation_sensitivity = 0.005 * (1.0 + (20.0 / data->view.zoom));
	pan_sensitivity = 1.5 * (data->view.zoom / 15.0);
	if (data->mouse.button == MOUSE_LEFT_BUTTON)
	{
		data->view.beta += delta_x * rotation_sensitivity;
		data->view.alpha += delta_y * rotation_sensitivity;
	}
	else if (data->mouse.button == MOUSE_RIGHT_BUTTON)
	{
		data->view.offset_x -= delta_x * pan_sensitivity;
		data->view.offset_y -= delta_y * pan_sensitivity;
	}
	data->mouse.last_x = wireframe_x;
	data->mouse.last_y = wireframe_y;
	return (0);
}

int handle_mouse_scroll(int button, int x, int y, t_data *data)
{
	(void)y;
	if (x < data->menu_width)
		return (0);
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

void init_mouse(t_data *data)
{
	data->mouse.is_pressed = 0;
	data->mouse.button = 0;
	data->mouse.last_x = 0;
	data->mouse.last_y = 0;
}

