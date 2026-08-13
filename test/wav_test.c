#include "../src/audio.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_init.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	const char* filename = "test.wav";
	FILE* file = fopen(filename, "rb");
	if (!file) {
		printf("No file\n");
		return -1;
	}
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* buffer = malloc(size);
	if (fread(buffer, 1, size, file) != size) {
		fprintf(stderr, "Invalid file read\n");	
		return -1;
	}
	PCM pcm = {0};
	if (readWavHeader(buffer, size, &pcm)) {
		return -1;
	}
	SDL_AudioSpec spec;
	if (convertPCMtoSDLSpec(&pcm, &spec)) {
		return -1;
	}
	
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioStream* stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL, NULL, NULL);
	SDL_ResumeAudioStreamDevice(stream);
	SDL_PutAudioStreamData(stream, buffer  + pcm.data_offset, pcm.size);
	int running = 1;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = 0;
			}
		}
	}
	return 0;
}
