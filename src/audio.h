#ifndef WAV_H
#define WAV_H

#include <stdio.h>

typedef struct {
	int freq;
	int num_channels;
	int block_align;
	int bytes_per_sample;
	int num_samples;
} PCM;

int readWav(FILE* file);

#endif
