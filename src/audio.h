#ifndef WAV_H
#define WAV_H

#include <stdio.h>

typedef struct {
	int freq;
	int num_channels;
	int bits_per_sample;
	size_t size;
	size_t data_offset;
} PCM;

int readWav(FILE* file);

#endif
