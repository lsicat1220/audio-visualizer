#include "../src/fft.h"
#include "../src/complex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ARR_LEN 2048

int main() {
	Complex output[ARR_LEN];
	double input[ARR_LEN];
	srand(ARR_LEN);
	for (int i = 0; i < ARR_LEN; i++) {
		input[i] = rand();	
	}	
	int i = 0;
	while (1) {
		printf("Run %d\r", i);	
		fflush(stdout);
		fft(input, ARR_LEN, output);
		i++;
		usleep(46440);
	}
	printf("\n");
}
