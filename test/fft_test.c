#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../src/complex.h"
#include "../src/fft.h"


double f(double x) {
	return sin(2 * M_PI * 15 * x) + sin(2 * M_PI * 2.3 * x);
}

double* linspace(int time, int N) {
	double* output = malloc(sizeof(double) * N);
	double stride = (double)time / N;
	double val = 0;
	for (int i = 0; i < N; i++) {
		output[i] = val;
		val += stride;
	}
	return output;
}

int main() {
	printf("Hello world!\n");
	int time = 8;
	int f_s = 512;
	int N = time * f_s;
	
	double* x = linspace(time, N);
	double* y = malloc(sizeof(double) * N);
	for (int i = 0; i < N; i++) {
		y[i] = f(x[i]);
	}
	
	clock_t start = clock();

	Complex* input = doubleToComplexArr(y, N);
	Complex* output1 = naive_fft(input, N, 1);

	clock_t end = clock();
	double exe_time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Naive FFT time elapsed: %lf\n", exe_time);

	start = clock();

	input = doubleToComplexArr(y, N);
	Complex* output2 = fft(input, N, 1);

	end = clock();
	exe_time = ((double) (end-start)) / CLOCKS_PER_SEC;
	printf("New FFT time elapsed: %lf\n", exe_time);

	int equal = 1;
	for (int i = 0; i < N; i++) {
		if (magnitude(output1[i]) - magnitude(output2[i]) > 0.000001) {
			equal = 0;
			break;
		}
	}
	printf("Equal: %d\n", equal);

	free(x);
	free(y);
	free(input);
	free(output1);
	free(output2);
	// free(output2);
	return 0;
}
