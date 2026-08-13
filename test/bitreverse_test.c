#include <stdio.h>
#include <time.h>
#define ARR_LEN 8192

int reverseBits(int power, int input);
int whatPowerOf2(int N);

int main() {
	int power = whatPowerOf2(ARR_LEN);
	printf("Power: %d\n", power);
	clock_t start = clock();
	for (int i = 0; i < ARR_LEN; i++) {
		reverseBits(power, i);
	}	
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Execution time: %lf\n", time);
	return 0;
}

