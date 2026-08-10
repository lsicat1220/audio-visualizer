#include "complex.h"
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Complex* dft(Complex* arr, int N) {
	Complex* output = malloc(sizeof(Complex) * N);
	memset(output, 0, sizeof(Complex) * N);
	for (int k = 0; k < N; k++) {
		// printf("k = %d\n", k);
		for (int n = 0; n < N; n++) {
			//printf("\tn = %d\n", n);
			Complex omega = complexExp(-2 * M_PI * ((double)k / (double)N) * n);
			Complex product = complexMult(arr[n], omega);
			output[k] = complexAdd(output[k], product);
			// printf("\t\toutput[k] = %lf + j%lf\n", output[k].real, output[k].imag);
		}
	}
	return output;
}

Complex* fft(Complex* arr, int N, int stride) {
	Complex* output = malloc(sizeof(Complex) * N);

	if ((N & N - 1) != 0)	{
		fputs("ERROR: Must be a power of 2\n", stderr);
		return NULL;
	} else if (N == 1) {
		output[0] = arr[0];
		return output;
	}

	Complex* evens = fft(arr, N/2, stride * 2);
	Complex* odds = fft(arr + stride, N/2, stride * 2);
	
	for(int k = 0; k < N/2; k++) {
		Complex omega = complexExp(-2 * M_PI * ((double)k / N));
		Complex product = complexMult(odds[k], omega);
		output[k] = complexAdd(evens[k], product);
		product.real *= -1;
		product.imag *= -1;
		output[k + N/2] = complexAdd(evens[k], product);
	}

	free(evens);
	free(odds);
	return output;
}
