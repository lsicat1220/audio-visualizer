#ifndef WAV_H
#define WAV_H

#include <stdio.h>
#include <SDL3/SDL_audio.h>

typedef struct {
	int freq;
	int num_channels;
	int bits_per_sample;
	size_t size;
	size_t data_offset;
} PCM;

int readWavHeader(unsigned char* buffer, size_t size, PCM* pcm);

int convertPCMtoSDLSpec(PCM* pcm, SDL_AudioSpec* output);

int readWav(FILE* file);

#endif
