/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:28:45 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/01 19:30:41 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stddef.h>

void	init_audio(t_data *data)
{
	const int	temp_ranges[] = {0, 8, 10, 20, 42, 85, 170, 300, 512};

	data->audio.enabled = false;
	data->audio.connected = false;
	data->audio.terminate = false;
	data->audio.buffer_size = 1024;
	data->audio.sample_rate = 44100;
	data->audio.scale_base = data->view.scale;
	data->audio.scale_multiplier = 0.5 + log10(data->map->radius);
	ft_memcpy(data->audio.band_ranges, temp_ranges, sizeof(temp_ranges));
	ft_memset(data->audio.buckets, 0, 8);
	data->audio.audio_samples = malloc(sizeof(float) * data->audio.buffer_size);
	if (!data->audio.audio_samples)
		return ;
	ft_memset(data->audio.audio_samples, 0, sizeof(float)
		* data->audio.buffer_size);
	pthread_mutex_init(&data->audio.audio_mutex, NULL);
	data->audio.pulse.stream = NULL;
	data->audio.pulse.running = false;
}

void	cleanup_audio(t_data *data)
{
	stop_pulse_audio(data);
	if (data->audio.audio_samples)
	{
		free(data->audio.audio_samples);
		data->audio.audio_samples = NULL;
	}
	pthread_mutex_destroy(&data->audio.audio_mutex);
}

int	calculate_audio_bucket_index(t_data *data, t_point *point)
{
	int		bucket_index;
	float	distance;

	if (data->view.view_mode == ISOMETRIC)
	{
		distance = sqrt((point->x * point->x) + (point->y * point->y));
		bucket_index = (int)((distance / data->map->max_distance) * 7.9f);
	}
	else
		bucket_index = 7 - (abs(point->x) * 8) / (data->map->map_width / 2);
	if (bucket_index < 0)
		bucket_index = 0;
	if (bucket_index >= 8)
		bucket_index = 7;
	return (bucket_index);
}

void	process_audio_samples(int16_t *samples, int sample_count, t_data *data)
{
	int	i;
	int	copy_count;

	i = -1;
	copy_count = fmin(sample_count, data->audio.buffer_size);
	pthread_mutex_lock(&data->audio.audio_mutex);
	while (++i < copy_count)
		data->audio.audio_samples[i] = (float)samples[i] / 32768.0f;
	pthread_mutex_unlock(&data->audio.audio_mutex);
}
