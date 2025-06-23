/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_audio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:45:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/23 03:16:49 by amagno-r         ###   ########.fr       */
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
		return;
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
		*raw_value *= 2.0f;
	else if (band == 1) 
		*raw_value *= 1.8f;
	else if (band == 2) 
		*raw_value *= 1.5f;
	else if (band == 3) 
		*raw_value *= 1.3f;
	else if (band == 4) 
		*raw_value *= 0.9f;
}

void	apply_eq_smoothing(float new_value, int band, t_data *data)
{
	static float smoothed_buckets[5] = {0.0f};
	float smoothing_factor;
	
	smoothing_factor = 0.15f;
	apply_equalizer(&new_value, band);
	smoothed_buckets[band] = smoothed_buckets[band] * (1.0f - smoothing_factor) + 
							 new_value * smoothing_factor;
	data->audio.buckets[band] = smoothed_buckets[band];
}

void	decay_bucket(int band, t_data *data)
{
	static float smoothed_buckets[5] = {0.0f};
	smoothed_buckets[band] *= 0.95f;
	data->audio.buckets[band] = smoothed_buckets[band];
}

void	simple_frequency_analysis(t_data *data)
{
	int i, band;
	float sample;
	float sum[5] = {0.0};
	int count[5] = {0};
	int band_ranges[6] = {0, 4, 12, 35, 120, 512};
	
	pthread_mutex_lock(&data->audio.audio_mutex);
	band = -1;
	while (++band < 5)
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
	int bucket_index;
	
	if (data->view.view_mode == ISOMETRIC)
	{
		float distance = sqrt((point->x * point->x) 
						+ (point->y * point->y));
		bucket_index = (int)((distance / data->map->max_distance) * 4.9f);
	}
	else
	{
		int normalized_x = point->x + (data->map->map_width / 2);
		bucket_index = (normalized_x * 5) / data->map->map_width;
	}
	if (bucket_index < 0) bucket_index = 0;
	if (bucket_index >= 5) bucket_index = 4;
	return (bucket_index);
}

void set_point_audio_scale(t_data *data, t_point *point)
{
	int bucket_index;
	float audio_multiplier;
	static double last_analysis_time = 0.0;
	double current_time = data->time;
	
	if (!data->audio.enabled || !data->audio.connected)
	{
		point->scale = data->view.scale;
		return ;
	}
	if (current_time != last_analysis_time)
	{
		simple_frequency_analysis(data);
		last_analysis_time = current_time;
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
	int copy_count = fmin(sample_count, data->audio.buffer_size);
	
	pthread_mutex_lock(&data->audio.audio_mutex);
	for (i = 0; i < copy_count; i++)
	{
		data->audio.audio_samples[i] = (float)samples[i] / 32768.0f;
	}
	pthread_mutex_unlock(&data->audio.audio_mutex);
}