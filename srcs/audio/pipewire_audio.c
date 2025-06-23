/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipewire_audio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagno-r <amagno-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:55:00 by amagno-r          #+#    #+#             */
/*   Updated: 2025/06/23 02:00:51 by amagno-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>
#include <pipewire/pipewire.h>
#include <spa/param/audio/format-utils.h>
#include <spa/param/props.h>

typedef struct s_pipewire_data
{
	struct pw_main_loop		*loop;
	struct pw_stream		*stream;
	struct spa_audio_info	format;
	t_data					*fdf_data;
	bool					running;
}	t_pipewire_data;

static void on_process(void *userdata)
{
	t_pipewire_data *pw_data = userdata;
	struct pw_buffer *b;
	struct spa_buffer *buf;
	uint32_t n_samples;
	int16_t *samples;

	if (!pw_data->fdf_data->audio.enabled || !pw_data->running)
		return;
	if ((b = pw_stream_dequeue_buffer(pw_data->stream)) == NULL) 
		return;
	buf = b->buffer;
	if (buf->datas[0].data == NULL) {
		pw_stream_queue_buffer(pw_data->stream, b);
		return;
	}
	samples = (int16_t *)buf->datas[0].data;
	n_samples = buf->datas[0].chunk->size / sizeof(int16_t);
	if (pw_data->fdf_data && pw_data->fdf_data->audio.enabled)
		process_audio_samples(samples, n_samples, pw_data->fdf_data);
	pw_stream_queue_buffer(pw_data->stream, b);
}

static void on_param_changed(void *userdata, uint32_t id, const struct spa_pod *param)
{
	t_pipewire_data *data = userdata;

	if (param == NULL || id != SPA_PARAM_Format)
		return;
	if (spa_format_parse(param, &data->format.media_type, &data->format.media_subtype) < 0)
		return;
	if (data->format.media_type != SPA_MEDIA_TYPE_audio ||
		data->format.media_subtype != SPA_MEDIA_SUBTYPE_raw)
		return;
	spa_format_audio_raw_parse(param, &data->format.info.raw);
}

static const struct pw_stream_events stream_events = {
	PW_VERSION_STREAM_EVENTS,
	.param_changed = on_param_changed,
	.process = on_process,
};

void *pipewire_audio_thread(void *arg)
{
	t_data *data = (t_data *)arg;
	t_pipewire_data pw_data = {0};
	const struct spa_pod *params[1];
	uint8_t buffer[1024];
	struct pw_properties *props;
	struct spa_pod_builder b = SPA_POD_BUILDER_INIT(buffer, sizeof(buffer));
	pw_data.fdf_data = data;
	pw_data.running = true;
	pw_init(NULL, NULL);
	pw_data.loop = pw_main_loop_new(NULL);
	if (!pw_data.loop) {
		data->audio.connected = false;
		return NULL;
	}
	data->audio.pw_loop = pw_data.loop;
	props = pw_properties_new(
		PW_KEY_MEDIA_TYPE, "Audio",
		PW_KEY_MEDIA_CATEGORY, "Capture",
		PW_KEY_MEDIA_ROLE, "Music",
		PW_KEY_STREAM_CAPTURE_SINK, "true",  // Capture system audio
		NULL);
	pw_data.stream = pw_stream_new_simple(
		pw_main_loop_get_loop(pw_data.loop),
		"FDF Audio Reactive",
		props,
		&stream_events,
		&pw_data);
	if (!pw_data.stream) {
		pw_main_loop_destroy(pw_data.loop);
		data->audio.connected = false;
		return NULL;
	}
	params[0] = spa_format_audio_raw_build(&b, SPA_PARAM_EnumFormat,
		&SPA_AUDIO_INFO_RAW_INIT(
			.format = SPA_AUDIO_FORMAT_S16,
			.rate = data->audio.sample_rate,
			.channels = 2));
	if (pw_stream_connect(pw_data.stream,
			PW_DIRECTION_INPUT,
			PW_ID_ANY,
			PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS,
			params, 1) < 0) {
		pw_stream_destroy(pw_data.stream);
		pw_main_loop_destroy(pw_data.loop);
		data->audio.connected = false;
		return NULL;
	}
	data->audio.connected = true;
	pw_main_loop_run(pw_data.loop);
	pw_stream_destroy(pw_data.stream);
	pw_main_loop_destroy(pw_data.loop);
	pw_deinit();
	data->audio.connected = false;
	return NULL;
}

bool start_pipewire_audio(t_data *data)
{
	if (data->audio.connected) {
		return true;
	}

	if (pthread_create(&data->audio.audio_thread, NULL, pipewire_audio_thread, data) != 0) {
		return false;
	}
	usleep(100000);  // 100ms
	return data->audio.connected;
}

void stop_pipewire_audio(t_data *data)
{
	if (!data->audio.connected)
		return;
	
	data->audio.connected = false;
	
	// Signal the PipeWire loop to quit
	if (data->audio.pw_loop)
		pw_main_loop_quit((struct pw_main_loop *)data->audio.pw_loop);
	
	// Now safely join the thread
	pthread_join(data->audio.audio_thread, NULL);
	
	// Clear the loop pointer
	data->audio.pw_loop = NULL;
}
