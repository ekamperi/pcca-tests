#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double complex z1 = 1.0 + 1.0 * I;

	assert(fabs(carg(z1) - M_PI_4) < 0.001);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
