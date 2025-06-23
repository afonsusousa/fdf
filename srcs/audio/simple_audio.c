/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_audio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:45:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/23 02:53:08 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stddef.h"
#include <math.h>
#include <stdio.h>

void	init_audio(t_data *data)
{
	int i;
	
	data->audio.enabled = false;
	data->audio.connected = false;
	data->audio.pw_loop = NULL;
	data->audio.buffer_size = 1024;
	data->audio.sample_rate = 44100;
	data->audio.scale_base = data->view.scale;
	data->audio.scale_multiplier = 0.5;  // Much smaller multiplier to match
	for (i = 0; i < 5; i++)
		data->audio.buckets[i] = 0.0;
	data->audio.fft_buffer = malloc(sizeof(float) * data->audio.buffer_size);
	data->audio.audio_samples = malloc(sizeof(float) * data->audio.buffer_size);
	if (!data->audio.fft_buffer || !data->audio.audio_samples)
	{
		return;
	}
	pthread_mutex_init(&data->audio.audio_mutex, NULL);
}

void	cleanup_audio(t_data *data)
{
	stop_pipewire_audio(data);
	
	if (data->audio.fft_buffer)
	{
		free(data->audio.fft_buffer);
		data->audio.fft_buffer = NULL;
	}
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
			if (start_pipewire_audio(data))
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
			stop_pipewire_audio(data);
			data->audio.connected = false;
		}
	}
}

void	apply_equalizer(float *raw_value, int band)
{
	if (band == 0) 
		*raw_value *= 2.0f;      // Boost sub-bass (20-80Hz) for deep bass lines
	else if (band == 1) 
		*raw_value *= 1.8f;      // Boost bass/kick (80-250Hz) for drums
	else if (band == 2) 
		*raw_value *= 1.5f;      // Boost low-mid (250-1kHz) for vocal warmth
	else if (band == 3) 
		*raw_value *= 1.3f;      // Boost mid (1-4kHz) for vocal presence
	else if (band == 4) 
		*raw_value *= 0.9f;      // Slightly reduce treble (4-20kHz) for smoothness
}

void	simple_frequency_analysis(t_data *data)
{
	int i, band;
	float sample;
	float sum[5] = {0.0};
	int count[5] = {0};
	int band_ranges[6] = {0, 4, 12, 35, 120, 512};
	static float smoothed_buckets[5] = {0.0f}; // Static for persistence
	float smoothing_factor = 0.2f; // Lower = smoother, higher = more responsive
	pthread_mutex_lock(&data->audio.audio_mutex);
	for (band = 0; band < 5; band++)
	{
		int start = band_ranges[band];
		int end = band_ranges[band + 1];
		for (i = start; i < end && i < data->audio.buffer_size; i++)
		{
			sample = fabs(data->audio.audio_samples[i]);
			sum[band] += sample * sample;
			count[band]++;
		}
		if (count[band] > 0)
		{
			float value = sqrt(sum[band] / count[band]);
			apply_equalizer(&value, band);
			smoothed_buckets[band] = smoothed_buckets[band] * (1.0f - smoothing_factor) + 
									 value * smoothing_factor;
			data->audio.buckets[band] = smoothed_buckets[band];
		}
		else
		{
			smoothed_buckets[band] *= 0.95f;
			data->audio.buckets[band] = smoothed_buckets[band];
		}
	}
	pthread_mutex_unlock(&data->audio.audio_mutex);
}

void set_point_audio_scale(t_data *data, t_point *point)
{
	int bucket_index;
	int normalized_x;
	float audio_multiplier;
	static double last_analysis_time = 0.0;
	static float last_scale = 1.0f;
	double current_time = data->time;
	float scale_smoothing = 0.08f;
	if (!data->audio.enabled || !data->audio.connected)
	{
		last_scale = last_scale * 0.95f + data->view.scale * 0.05f;
		point->scale = last_scale;
		return ;
	}
	if (current_time != last_analysis_time)
	{
		simple_frequency_analysis(data);
		last_analysis_time = current_time;
	}
	if (data->view.view_mode == ISOMETRIC)
	{
		float distance = sqrt((point->x * point->x) 
						+ (point->y * point->y));
		bucket_index = (int)((distance / data->map->max_distance) * 4.9f);
	}
	else
	{
		normalized_x = point->x + (data->map->map_width / 2);
		bucket_index = (normalized_x * 5) / data->map->map_width;
	}
	if (bucket_index < 0) bucket_index = 0;
	if (bucket_index >= 5) bucket_index = 4;
	audio_multiplier = data->view.scale + (data->audio.buckets[bucket_index] 
		* data->audio.scale_multiplier);
	audio_multiplier = fmax(0.1, fmin(audio_multiplier, 3.0));
	float target_scale = audio_multiplier * 0.2;
	last_scale = last_scale * (1.0f - scale_smoothing) + target_scale * scale_smoothing;
	point->scale = last_scale;
}

void	process_audio_samples(int16_t *samples, int sample_count, t_data *data)
{
	int i;
	int copy_count = fmin(sample_count, data->audio.buffer_size);
	
	pthread_mutex_lock(&data->audio.audio_mutex);
	for (i = 0; i < copy_count; i++)
	{
		data->audio.audio_samples[i] = (float)samples[i] / 32768.0f;
	}
	pthread_mutex_unlock(&data->audio.audio_mutex);
}