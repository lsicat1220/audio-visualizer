#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "wav.h"



int readWav(FILE* file, PCM* output) {
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
