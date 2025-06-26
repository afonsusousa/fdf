/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulseaudio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:33:23 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/26 04:20:58 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <pthread.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#include <stdlib.h>
#include <unistd.h>

static bool	init_pulse_stream(t_data *data)
{
	pa_sample_spec	ss;
	pa_buffer_attr	pb;
	int				error;

	ss.format = PA_SAMPLE_S16LE;
	ss.rate = data->audio.sample_rate;
	ss.channels = 1;
	pb.maxlength = (uint32_t)-1;
	pb.fragsize = data->audio.buffer_size * sizeof(int16_t);
	data->audio.pulse.stream = pa_simple_new(NULL, "FDF Audio Visualizer",
			PA_STREAM_RECORD, "@DEFAULT_MONITOR@", "Audio for FDF", &ss, NULL,
			&pb, &error);
	if (!data->audio.pulse.stream)
	{
		data->audio.connected = false;
		data->audio.pulse.running = false;
		return (false);
	}
	data->audio.connected = true;
	return (true);
}

void	*pulse_audio_thread(void *arg)
{
	t_data	*data;
	int16_t	*buf;
	int		error;

	data = (t_data *)arg;
	buf = malloc(data->audio.buffer_size * sizeof(int16_t));
	if (!buf)
		return (NULL);
	if (!init_pulse_stream(data))
		return (free(buf), NULL);
	while (data->audio.pulse.running && !data->audio.terminate
		&& pa_simple_read((pa_simple *)data->audio.pulse.stream, buf,
			data->audio.buffer_size * sizeof(int16_t), &error) >= 0)
	{
		process_audio_samples(buf, data->audio.buffer_size, data);
	}
	if (data->audio.pulse.stream)
	{
		pa_simple_free((pa_simple *)data->audio.pulse.stream);
		data->audio.pulse.stream = NULL;
	}
	data->audio.connected = false;
	data->audio.pulse.running = false;
	return (free(buf), NULL);
}

bool	start_pulse_audio(t_data *data)
{
	if (data->audio.connected)
	{
		ft_printf("PulseAudio already running\n");
		return (true);
	}
	data->audio.terminate = false;
	data->audio.pulse.running = true;
	if (pthread_create(&data->audio.pulse.thread, NULL, pulse_audio_thread,
			data) != 0)
	{
		ft_printf("Failed to create PulseAudio thread\n");
		data->audio.pulse.running = false;
		return (false);
	}
	usleep(100000);
	if (!data->audio.connected)
	{
		ft_printf("PulseAudio thread failed to start\n");
		return (false);
	}
	return (true);
}

void	stop_pulse_audio(t_data *data)
{
	if (!data->audio.connected)
		return ;
	data->audio.terminate = true;
	data->audio.connected = false;
	data->audio.pulse.running = false;
	pthread_join(data->audio.pulse.thread, NULL);
	if (data->audio.pulse.stream)
	{
		pa_simple_free((pa_simple *)data->audio.pulse.stream);
		data->audio.pulse.stream = NULL;
	}
}
