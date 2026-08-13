#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL3/SDL_audio.h>
#include "audio.h"

int convertPCMtoSDLSpec(PCM* pcm, SDL_AudioSpec* output) {
	output->channels = pcm->num_channels;
	output->freq = pcm->freq;
	if (pcm->bits_per_sample == 8) {
		output->format = SDL_AUDIO_U8;
	} else if (pcm->bits_per_sample == 16) {
		output->format = SDL_AUDIO_S16;
	} else {
		fprintf(stderr, "ERROR: Invalid or unsupported bits per sample\n");
		return -1;
	}
	return 0;	
}

int readWavHeader(unsigned char* buffer, size_t size, PCM* pcm) {
	// Ensure a state for the pcm that the function can check
	memset(pcm, 0, sizeof(PCM));
	if (size < 12) {
		fprintf(stderr, "ERROR: Buffer too small to contain WAV data\n");
		return -1;
	}	
	if (memcmp(buffer, "RIFF", 4) != 0|| memcmp(buffer + 8, "WAVE", 4)) {
		fprintf(stderr, "ERROR: Not a valid .wav file\n");
		return -1;
	}
	uint32_t filesize = ((uint32_t) buffer[4]) | 
		((uint32_t)buffer[5]<<8) | 
		((uint32_t)buffer[6]<<16) | 
		((uint32_t)buffer[7]<<24);
	if (filesize > size) {
		fprintf(stderr, "ERROR: Insufficient buffer\n");
		return -1;
	}
	unsigned char* ptr = buffer + 12;		
	while (ptr - buffer < filesize) {
		uint32_t chunk_size = ((uint32_t) ptr[4]) | 
			((uint32_t)ptr[5]<<8) | 
			((uint32_t)ptr[6]<<16) | 
			((uint32_t)ptr[7]<<24);
		if (memcmp(ptr, "fmt ", 4) == 0) {
			if (*(ptr + 8) != 0x01) {
				fprintf(stderr, "ERROR: Unsupported WAV format\n");
				return -1;
			}	
			pcm->freq = ((uint32_t) ptr[12]) | 
				((uint32_t)ptr[13]<<8) | 
				((uint32_t)ptr[14]<<16) | 
				((uint32_t)ptr[15]<<24);
			pcm->num_channels = ((uint32_t) ptr[10]) | ((uint32_t) ptr[11]<<8);
			pcm->bits_per_sample = ((uint32_t) ptr[22]) | ((uint32_t) ptr[23]<<8);
		} else if (memcmp(ptr, "data", 4) == 0) {
			pcm->size = ((uint32_t) ptr[4]) | 
				((uint32_t)ptr[5]<<8) | 
				((uint32_t)ptr[6]<<16) | 
				((uint32_t)ptr[7]<<24);
			pcm->data_offset = (ptr - buffer) + 8;
		}
		ptr += (8 + chunk_size);
	}
	return 0;
}

int readWav(FILE* file) {
	unsigned char master[12];
	if (fread(master, 1, 12, file) != 12) {
		fprintf(stderr, "ERROR: Reading .wav header failed\n");
		return -1;
	}
	if (memcmp(master, "RIFF", 4) != 0|| memcmp(master + 8, "WAVE", 4)) {
		fprintf(stderr, "ERROR: Not a valid .wav file\n");
		return -1;
	}
	uint32_t filesize = ((uint32_t) master[4]) | 
		((uint32_t)master[5]<<8) | 
		((uint32_t)master[6]<<16) | 
		((uint32_t)master[7]<<24);
	filesize -= 4;
	unsigned char* buffer = malloc(filesize);
	if (fread(buffer, 1, filesize, file) != filesize) {
		fprintf(stderr, "ERROR: Reading file failed -- File size mismatch\n");
		free(buffer);
		return -1;
	}
	unsigned char* ptr = buffer;		
	while (ptr - buffer < filesize) {
		printf("Chunk ID: %.4s\n", ptr);
		uint32_t chunk_size = ((uint32_t) ptr[4]) | 
			((uint32_t)ptr[5]<<8) | 
			((uint32_t)ptr[6]<<16) | 
			((uint32_t)ptr[7]<<24);
		printf("Size: %d\n", chunk_size);
		ptr += (8 + chunk_size);
	}

	return 0;
}
