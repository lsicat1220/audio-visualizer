#include <stdio.h>
#include <string.h>
#include "wav.h"

int ReadWavHeader(FILE* file, PCM* output) {
	char buffer[128];
	if (fread(buffer, 1, 12, file) != 12) {
		fprintf(stderr, "ERROR: Reading .wav header failed\n");
		return -1;
	}
	if (memcmp(buffer, "RIFF", 4) != 0|| memcmp(buffer + 8, "WAVE", 4)) {
		fprintf(stderr, "ERROR: Not a valid .wav file\n");
		return -1;
	}
	
	return 0;
}
