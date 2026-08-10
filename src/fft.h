#ifndef FFT_H
#define FFT_H

#include "complex.h"

Complex* fft(Complex* arr, int N, int stride);

Complex* dft(Complex* arr, int N);

#endif
