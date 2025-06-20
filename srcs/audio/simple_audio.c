/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_audio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:45:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/20 01:24:05 by amagno-r         ###   ########.fr       */
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
		data->audio.scale_base = data->view.scale;
	else
		data->view.scale = data->audio.scale_base;
}

void	simple_frequency_analysis(t_data *data)
{
	int i, band;
	float sample;
	int samples_per_band = data->audio.buffer_size / 5;
	float sum[5] = {0.0};
	
	pthread_mutex_lock(&data->audio.audio_mutex);
	
	for (band = 0; band < 5; band++)
	{
		int start = band * samples_per_band;
		int end = (band == 4) ? data->audio.buffer_size : (band + 1) * samples_per_band;
		
		for (i = start; i < end; i++)
		{
			sample = fabs(data->audio.audio_samples[i]);
			sum[band] += sample * sample;
		}
		
		data->audio.buckets[band] = sqrt(sum[band] / (end - start));
	}
	pthread_mutex_unlock(&data->audio.audio_mutex);
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
	int normalized_x = point->x + (data->map->map_width / 2);
	bucket_index = (normalized_x * 5) / data->map->map_width;
	if (bucket_index < 0) bucket_index = 0;
	if (bucket_index >= 5) bucket_index = 4;
	audio_multiplier = 1.0 + (data->audio.buckets[bucket_index] * data->audio.scale_multiplier);
	audio_multiplier = fmax(0.1, fmin(audio_multiplier, 3.0));
	point->scale = audio_multiplier;
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

void	increase_audio_sensitivity(t_data *data)
{
	data->audio.scale_multiplier = fmin(data->audio.scale_multiplier + 0.05, 1.0);  // Smaller increments and max
	printf("Audio sensitivity: %.2f\n", data->audio.scale_multiplier);
}

void	decrease_audio_sensitivity(t_data *data)
{
	data->audio.scale_multiplier = fmax(data->audio.scale_multiplier - 0.05, 0.01);  // Smaller increments and min
	printf("Audio sensitivity: %.2f\n", data->audio.scale_multiplier);
}

void	reset_audio_settings(t_data *data)
{
	data->audio.scale_multiplier = 0.2;  // Reset to smaller default
	data->audio.scale_base = 1.0;
	data->view.scale = 1.0;
	printf("Audio settings reset\n");
}
