/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:00:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/11 17:55:41 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <stdbool.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef union u_color
{
	int				hex;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}	s_rgba;
}					t_color;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				display[2];
	double			world_3d[3];
	double			axial[2];
	t_color			color;
	bool			colored;
	float			scale;
}					t_point;

typedef struct s_line_info
{
	t_point			*p0;
	t_point			*p1;
	float			depth;
}					t_line_info;

typedef struct s_line
{
	float			dx;
	float			dy;
	float			slope;
	int				x_start;
	int				x_end;
	float			current_y;
	bool			steep;
	t_color			color1;
	t_color			color2;
}					t_line;

typedef enum e_render_mode
{
	RENDER_PRIORITY = 0,
	RENDER_BRAINFUCK_PRIORITY = 1,
	RENDER_TRAVERSAL = 2
}					t_render_mode;

typedef enum e_view_mode
{
	ISOMETRIC = 0,
	ORTOGRAPHIC = 1,
	SPHERICAL = 2,
	CYLINDRICAL = 3
}					t_view_mode;

typedef struct s_ripple
{
	bool			enabled;
	int				amplitude;
	double			k;
	double			angular_freq;
	double			distance;
	double			propagation_speed;
	double			time;
}					t_ripple;

typedef struct s_wave
{
	bool			enabled_x;
	bool			enabled_y;
	int				amplitude;
	double			k;
	double			angular_freq_x;
	double			angular_freq_y;
	double			propagation_speed_x;
	double			propagation_speed_y;
	double			distance;
	double			x_time;
	double			y_time;
}					t_wave;

typedef struct s_view
{
	int				off_x;
	int				off_y;
	double			alpha;
	double			beta;
	double			gamma;
	double			scale;
	double			angle;
	int				zoom;
	float			brange;
	bool			bend;
	int				auto_rotate;
	double			axis[3];
	bool			top_down;
	bool			dvd;
	t_ripple		ripple;
	t_wave			wave;
	t_render_mode	render_mode;
	t_view_mode		view_mode;
}					t_view;

typedef struct s_map
{
	int					map_width;
	int					map_height;
	int					points_count;
	int					line_capacity;
	int					max_z;
	int					min_z;
	int					max_distance;
	float				radius;
	t_point				*points;
	t_point				*center;
	t_line_info			*lines;
}					t_map;

typedef struct s_mouse
{
	int				is_pressed;
	int				button;
	int				last_x;
	int				last_y;
}					t_mouse;

# ifdef AUDIO

typedef struct s_pulse_state
{
	void			*stream;
	pthread_t		thread;
	bool			running;
	bool			thread_created;
}					t_pulse_state;

typedef struct s_audio
{
	bool			enabled;
	bool			connected;
	bool			terminate;
	float			*audio_samples;
	int				buffer_size;
	int				sample_rate;
	float			buckets[8];
	int				band_ranges[9];
	float			scale_multiplier;
	float			scale_base;
	pthread_t		audio_thread;
	pthread_mutex_t	audio_mutex;
	t_pulse_state	pulse;
}					t_audio;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				w_height;
	int				w_width;
	int				m_ratio;
	int				m_width;
	unsigned int	pixel_count;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			time;
	t_map			*map;
	t_view			view;
	t_mouse			mouse;
	t_audio			audio;
	bool			keys[16];
}					t_data;

# else

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				w_height;
	int				w_width;
	int				m_ratio;
	int				m_width;
	int				pixel_count;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			time;
	t_map			*map;
	t_view			view;
	t_mouse			mouse;
	bool			keys[16];
}					t_data;

# endif

typedef struct s_axis_params
{
	double			*axis;
	int				end[2];
	int				color;
}					t_axis_params;

typedef struct s_pixel_values
{
	int				y_pixel;
	float			y_fract;
	float			y_rfract;
}					t_pixel_values;

#endif
