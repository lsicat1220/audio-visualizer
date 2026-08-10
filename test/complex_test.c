#include "../src/complex.h"
#include <stdio.h>
#include <math.h>

int main() {
	Complex num;
	for (int i = 0; i < 8; i++) {
		num = complexExp(-2 * M_PI * ((double)i / 8));
		printf("%lf + j%lf\n", num.real, num.imag);
	}
	return 0;
}
