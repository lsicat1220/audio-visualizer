#ifndef FFT_H
#define FFT_H

#include "complex.h"

Complex* recursive_fft(Complex* arr, int N, int stride);

Complex* naive_fft(Complex* arr, int N, int stride);

Complex* dft(Complex* arr, int N);
 
Complex* fft(double* arr, int N, Complex* output);

#endif
