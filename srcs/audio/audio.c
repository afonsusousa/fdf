/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:45:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/26 03:46:24 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stddef.h"
#include <math.h>
#include <stdio.h>

void	toggle_audio_reactive(t_data *data)
{
	data->audio.enabled = !data->audio.enabled;
	if (data->audio.enabled)
	{
		data->audio.scale_base = data->view.scale;
		if (!data->audio.connected)
		{
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
			stop_pulse_audio(data);
			data->audio.connected = false;
		}
	}
}

void	apply_eq_smoothing(float new_value, int band, t_audio *audio)
{
	static float	smoothed_buckets[8] = {0.0f};
	const float		smoothing_factor = 0.075f;

	if (band == 0)
		new_value *= 2.0f;
	else if (band == 1)
		new_value *= 2.5f;
	else if (band == 2)
		new_value *= 2.2f;
	else if (band == 3)
		new_value *= 1.4f;
	else if (band == 4)
		new_value *= 1.9f;
	else if (band == 5)
		new_value *= 1.8f;
	else if (band == 6)
		new_value *= 1.5f;
	else if (band == 7)
		new_value *= 1.3f;
	smoothed_buckets[band] = smoothed_buckets[band] * (1.0f - smoothing_factor)
		+ new_value * smoothing_factor;
	audio->buckets[band] = smoothed_buckets[band];
}

void	decay_bucket(int band, t_audio *audio)
{
	static float	smoothed_buckets[8] = {0.0f};

	smoothed_buckets[band] *= 0.95f;
	audio->buckets[band] = smoothed_buckets[band];
}

void	simple_frequency_analysis(t_audio *audio)
{
	int			i;
	int			band;
	float		sample;
	float		sum[8];
	int			count[8];

	ft_memset(sum, 0, 8 * sizeof(float));
	ft_memset(count, 0, 8 * sizeof(int));
	pthread_mutex_lock(&audio->audio_mutex);
	band = -1;
	while (++band < 8)
	{
		i = audio->band_ranges[band] - 1;
		while (++i < audio->band_ranges[band + 1] && i < audio->buffer_size)
		{
			sample = fabs(audio->audio_samples[i]);
			sum[band] += sample * sample;
			count[band]++;
		}
		if (count[band] > 0)
			apply_eq_smoothing(sqrt(sum[band] / count[band]), band, audio);
		else
			decay_bucket(band, audio);
	}
	pthread_mutex_unlock(&audio->audio_mutex);
}

void	set_point_audio_scale(t_data *data, t_point *point)
{
	int				bucket_index;
	float			audio_multiplier;
	static double	last_analysis_time = 0.0;

	if (!data->audio.enabled || !data->audio.connected)
	{
		point->scale = data->view.scale;
		return ;
	}
	if (data->time != last_analysis_time)
	{
		simple_frequency_analysis(&data->audio);
		last_analysis_time = data->time;
	}
	bucket_index = calculate_audio_bucket_index(data, point);
	audio_multiplier = data->view.scale + (data->audio.buckets[bucket_index]
			* data->audio.scale_multiplier);
	audio_multiplier = fmax(0.1, fmin(audio_multiplier, 3.0));
	point->scale = audio_multiplier * 0.2;
}
