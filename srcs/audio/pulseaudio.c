#include "fdf.h"
#include <pulse/error.h>
#include <pulse/pulseaudio.h>
#include <pulse/simple.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static pa_simple *pulse_stream = NULL;
static pthread_t pulse_thread;
static bool pulse_running = false;

void *pulse_audio_thread(void *arg)
{
	t_data *data = (t_data *)arg;
	uint16_t buffer_size = data->audio.buffer_size;
	int16_t buf[buffer_size];
	int error;
	
	/* Sample format for 44.1kHz stereo 16-bit */
	static const pa_sample_spec ss = {
		.format = PA_SAMPLE_S16LE,
		.rate = 44100,
		.channels = 2
	};
	
	pa_buffer_attr pb = {
		.maxlength = (uint32_t)-1,
		.fragsize = buffer_size * sizeof(int16_t)
	};
	
	/* Connect to default PulseAudio sink monitor */
	pulse_stream = pa_simple_new(NULL, "FDF Audio Visualizer", PA_STREAM_RECORD, 
								NULL, "Audio for FDF", &ss, NULL, &pb, &error);
	
	if (!pulse_stream) {
		printf("PulseAudio connection failed: %s\n", pa_strerror(error));
		pulse_running = false;
		return NULL;
	}
	
	printf("PulseAudio connected successfully\n");
	
	while (pulse_running && !data->audio.terminate) {
		if (pa_simple_read(pulse_stream, buf, sizeof(buf), &error) < 0) {
			printf("PulseAudio read error: %s\n", pa_strerror(error));
			break;
		}
		
		/* Process audio samples for FDF */
		process_audio_samples(buf, buffer_size, data);
		
		usleep(10000); // 10ms sleep to prevent CPU overload
	}
	
	if (pulse_stream) {
		pa_simple_free(pulse_stream);
		pulse_stream = NULL;
	}
	
	pulse_running = false;
	printf("PulseAudio thread terminated\n");
	return NULL;
}

bool start_pulse_audio(t_data *data)
{
	if (pulse_running) {
		printf("PulseAudio already running\n");
		return true;
	}
	
	data->audio.terminate = false;
	pulse_running = true;
	
	if (pthread_create(&pulse_thread, NULL, pulse_audio_thread, data) != 0) {
		printf("Failed to create PulseAudio thread\n");
		pulse_running = false;
		return false;
	}
	
	/* Give thread time to initialize */
	usleep(100000); // 100ms
	
	if (!pulse_running) {
		printf("PulseAudio thread failed to start\n");
		return false;
	}
	
	printf("PulseAudio started successfully\n");
	return true;
}

void stop_pulse_audio(t_data *data)
{
	if (!pulse_running) {
		return;
	}
	
	printf("Stopping PulseAudio...\n");
	data->audio.terminate = true;
	pulse_running = false;
	
	/* Wait for thread to finish */
	pthread_join(pulse_thread, NULL);
	
	if (pulse_stream) {
		pa_simple_free(pulse_stream);
		pulse_stream = NULL;
	}
	
	printf("PulseAudio stopped\n");
}