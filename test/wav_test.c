#include "../src/audio.h"
#include <stdio.h>

int main() {
	const char* filename = "test.wav";
	FILE* file = fopen(filename, "rb");
	if (!file) {
		printf("No file\n");
		return -1;
	}
	readWav(file, NULL);
	return 0;
}
