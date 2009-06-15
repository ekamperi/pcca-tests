#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double complex z = 3.513 + 4.596 * I;

	assert(fabs(cimag(z) - 4.596) < 0.001);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
