/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pulseaudio_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:33:23 by amagno-r          #+#    #+#             */
/*   Updated: 2025/07/07 18:26:48 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <pthread.h>
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#include <stdlib.h>
#include <unistd.h>

static void	set_two_false(bool *one, bool *two)
{
	*one = false;
	*two = false;
}

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
		return (set_two_false(&data->audio.connected,
				&data->audio.pulse.running), false);
	data->audio.connected = true;
	return (true);
}

void	*pulse_audio_thread(void *arg)
{
	t_audio	*audio;
	int16_t	*buf;
	int		error;

	audio = &((t_data *)arg)->audio;
	buf = malloc(audio->buffer_size * sizeof(int16_t));
	if (!buf)
		return (set_two_false(&audio->pulse.running, &audio->connected), NULL);
	if (!init_pulse_stream((t_data *)arg))
		return (set_two_false(&audio->pulse.running, &audio->connected),
			free(buf), NULL);
	while (audio->pulse.running && !audio->terminate
		&& pa_simple_read((pa_simple *)audio->pulse.stream, buf,
			audio->buffer_size * sizeof(int16_t), &error) >= 0)
	{
		process_audio_samples(buf, audio->buffer_size, (t_data *)arg);
	}
	if (audio->pulse.stream && audio->pulse.running)
	{
		pa_simple_free((pa_simple *)audio->pulse.stream);
		audio->pulse.stream = NULL;
	}
	return (set_two_false(&audio->pulse.running, &audio->connected), NULL);
}

bool	start_pulse_audio(t_data *data)
{
	int	attempts;

	attempts = 0;
	if (data->audio.connected && data->audio.pulse.running)
		return (true);
	if (data->audio.pulse.thread_created)
		stop_pulse_audio(data);
	data->audio.terminate = false;
	data->audio.pulse.running = true;
	data->audio.connected = false;
	data->audio.pulse.thread_created = false;
	if (pthread_create(&data->audio.pulse.thread, NULL, pulse_audio_thread,
			data) != 0)
	{
		data->audio.pulse.running = false;
		return (false);
	}
	data->audio.pulse.thread_created = true;
	while (attempts++ < 20 && data->audio.pulse.running
		&& !data->audio.connected)
		usleep(25000);
	if (!data->audio.connected || !data->audio.pulse.running)
		return (stop_pulse_audio(data), false);
	return (true);
}

void	stop_pulse_audio(t_data *data)
{
	if (!data->audio.pulse.thread_created)
		return ;
	data->audio.terminate = true;
	data->audio.pulse.running = false;
	pthread_join(data->audio.pulse.thread, NULL);
	data->audio.pulse.thread_created = false;
	data->audio.connected = false;
	if (data->audio.pulse.stream)
	{
		pa_simple_free((pa_simple *)data->audio.pulse.stream);
		data->audio.pulse.stream = NULL;
	}
}
