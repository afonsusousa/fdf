/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_audio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:45:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/25 22:18:07 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stddef.h"
#include <math.h>
#include <stdio.h>

void	init_audio(t_data *data)
{
	data->audio.enabled = false;
	data->audio.connected = false;
	data->audio.pw_loop = NULL;
	data->audio.buffer_size = 1024;
	data->audio.sample_rate = 44100;
	data->audio.scale_base = data->view.scale;
	data->audio.scale_multiplier = 0.8;
	ft_memset(data->audio.buckets, 0, 8);
	data->audio.audio_samples = malloc(sizeof(float) * data->audio.buffer_size);
	if (!data->audio.audio_samples)
		return;
	pthread_mutex_init(&data->audio.audio_mutex, NULL);
}

void	cleanup_audio(t_data *data)
{
	// stop_pipewire_audio(data);
	stop_pulse_audio(data);
	if (data->audio.audio_samples)
	{
		free(data->audio.audio_samples);
		data->audio.audio_samples = NULL;
	}
	pthread_mutex_destroy(&data->audio.audio_mutex);
}

void	toggle_audio_reactive(t_data *data)
{
	data->audio.enabled = !data->audio.enabled;
	if (data->audio.enabled)
	{
		data->audio.scale_base = data->view.scale;
		if (!data->audio.connected)
		{
			// if (start_pipewire_audio(data))
			if (start_pulse_audio(data))
				data->audio.connected = true;
			else
				data->audio.enabled = false;
		}
	}
	else
	{
		data->view.scale = data->audio.scale_base;
		if (data->audio.connected)
		{
			// stop_pipewire_audio(data);
			stop_pulse_audio(data);
			data->audio.connected = false;
		}
	}
}

void	apply_equalizer(float *raw_value, int band)
{
	if (band == 0) 
		*raw_value *= 2.0f;    // Deep sub-bass (20-50Hz)
	else if (band == 1) 
		*raw_value *= 2.5f;    // Sub-kick (50-100Hz) - Maximum punch
	else if (band == 2) 
		*raw_value *= 2.2f;    // Kick fundamental (100-200Hz)
	else if (band == 3) 
		*raw_value *= 1.4f;    // Low-mid warmth (200-500Hz)
	else if (band == 4) 
		*raw_value *= 1.9f;    // Vocal presence (500-1.2kHz)
	else if (band == 5) 
		*raw_value *= 1.8f;    // Vocal clarity (1.2-2.5kHz)
	else if (band == 6) 
		*raw_value *= 1.5f;    // High-mid sparkle (2.5-5kHz)
	else if (band == 7) 
		*raw_value *= 1.3f;    // Air and brilliance (5-10kHz)
}

void	apply_eq_smoothing(float new_value, int band, t_data *data)
{
	static float smoothed_buckets[8] = {0.0f};
	const float smoothing_factor = 0.075f;

	apply_equalizer(&new_value, band);
	smoothed_buckets[band] = smoothed_buckets[band] * (1.0f - smoothing_factor) + 
							 new_value * smoothing_factor;
	data->audio.buckets[band] = smoothed_buckets[band];
}

void	decay_bucket(int band, t_data *data)
{
	static float smoothed_buckets[8] = {0.0f};
	
	smoothed_buckets[band] *= 0.95f;
	data->audio.buckets[band] = smoothed_buckets[band];
}

void	simple_frequency_analysis(t_data *data)
{
	int i, band;
	float sample;
	float sum[8];
	int count[8];
	const int band_ranges[9] = {0, 8, 10, 20, 42, 85, 170, 300, 512};
	
	ft_memset(sum, 0, 8 * sizeof(float));
	ft_memset(count, 0, 8 * sizeof(int));
	pthread_mutex_lock(&data->audio.audio_mutex);
	band = -1;
	while (++band < 8)
	{
		i = band_ranges[band] - 1;
		while (++i < band_ranges[band + 1] && i < data->audio.buffer_size)
		{
			sample = fabs(data->audio.audio_samples[i]);
			sum[band] += sample * sample;
			count[band]++;
		}
		if (count[band] > 0)
			apply_eq_smoothing(sqrt(sum[band] / count[band]), band, data);
		else
			decay_bucket(band, data);
	}
	pthread_mutex_unlock(&data->audio.audio_mutex);
}

int	calculate_audio_bucket_index(t_data *data, t_point *point)
{
	int		bucket_index;
	float	distance;
	
	if (data->view.view_mode == ISOMETRIC)
	{
		distance = sqrt((point->x * point->x) 
						+ (point->y * point->y));
		bucket_index = (int)((distance / data->map->max_distance) * 7.9f);
	}
	else
		bucket_index = 8 - (abs(point->x) * 8) / (data->map->map_width / 2);
	if (bucket_index < 0)
		bucket_index = 0;
	if (bucket_index >= 8)
		bucket_index = 7;
	return (bucket_index);
}

void set_point_audio_scale(t_data *data, t_point *point)
{
	int bucket_index;
	float audio_multiplier;
	static double last_analysis_time = 0.0;
	
	if (!data->audio.enabled || !data->audio.connected)
	{
		point->scale = data->view.scale;
		return ;
	}
	if (data->time != last_analysis_time)
	{
		simple_frequency_analysis(data);
		last_analysis_time = data->time;
	}
	bucket_index = calculate_audio_bucket_index(data, point);
	audio_multiplier = data->view.scale + (data->audio.buckets[bucket_index] 
		* data->audio.scale_multiplier);
	audio_multiplier = fmax(0.1, fmin(audio_multiplier, 3.0));
	point->scale = audio_multiplier * 0.2;
}

void	process_audio_samples(int16_t *samples, int sample_count, t_data *data)
{
	int i;
	int copy_count;
	
	i = -1;
	copy_count = fmin(sample_count, data->audio.buffer_size);
	pthread_mutex_lock(&data->audio.audio_mutex);
	while (++i < copy_count)
		data->audio.audio_samples[i] = (float)samples[i] / 32768.0f;
	pthread_mutex_unlock(&data->audio.audio_mutex);
}