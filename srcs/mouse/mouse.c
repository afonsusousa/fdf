/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:24:29 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/10 22:52:18 by amagno-r         ###   ########.fr       */
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
	// Only respond to mouse events in the wireframe area (not in the menu)
	if (x < data->menu_width)
		return (0);
	
	data->mouse.is_pressed = 1;
	// Store simple wireframe-relative coordinates
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
	
	// Only respond to mouse events in the wireframe area (not in the menu)
	if (x < data->menu_width)
	{
		data->mouse.is_pressed = 0; // Release if mouse moves into menu
		return (0);
	}
	
	// Convert to wireframe area coordinates (simple offset, no centering)
	wireframe_x = x - data->menu_width;
	wireframe_y = y;
	
	// Calculate mouse movement delta
	delta_x = wireframe_x - data->mouse.last_x;
	delta_y = wireframe_y - data->mouse.last_y;
	
	// Adaptive sensitivity based on zoom level
	rotation_sensitivity = 0.005 * (1.0 + (20.0 / data->view.zoom));
	pan_sensitivity = 1.5 * (data->view.zoom / 15.0);
	
	if (data->mouse.button == MOUSE_LEFT_BUTTON)
	{
		// INTUITIVE ISOMETRIC ROTATION:
		// Think of it like rotating a physical object on a table
		
		// Horizontal drag: Spin object left/right (Y-axis rotation)
		// This is the most natural movement - like turning a globe
		data->view.beta += delta_x * rotation_sensitivity;
		
		// Vertical drag: Tilt object up/down (X-axis rotation) 
		// Like tilting a book to see it from above or below
		data->view.alpha += delta_y * rotation_sensitivity;
		
		// No automatic gamma (roll) - keep it pure and predictable
	}
	else if (data->mouse.button == MOUSE_RIGHT_BUTTON)
	{
		// INTUITIVE CAMERA/VIEW CONTROLS:
		// Think of it like moving your viewpoint
		
		// Horizontal drag: Move view left/right (pan)
		data->view.offset_x -= delta_x * pan_sensitivity;
		
		// Vertical drag: Move view up/down (pan)
		data->view.offset_y -= delta_y * pan_sensitivity;
	}
	
	// Update last position for next frame
	data->mouse.last_x = wireframe_x;
	data->mouse.last_y = wireframe_y;
	return (0);
}

int handle_mouse_scroll(int button, int x, int y, t_data *data)
{
	(void)y;
	
	// Only respond to scroll events in the wireframe area (not in the menu)
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

