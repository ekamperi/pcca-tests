#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double complex z1 = 3.513 + 4.596 * I;
	double complex z2 = 3.513 - 4.596 * I;

	assert(fabs(cimag(conj(z1)) + 4.596) < 0.001);
	assert(fabs(cimag(conj(z2)) - 4.596) < 0.001);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
