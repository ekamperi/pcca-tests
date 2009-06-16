#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double complex z1 = 1.0 + 1.0 * I;
	double complex z2;
	double y;

	assert(fabs(carg(z1) - M_PI_4) < 0.001);

	/* Make sure that the return value is in the [-pi, +pi] interval. */
	for (y = -2.0; y < 2.0; y += 0.05) {
		z2 = 1.0 + y * I;
		assert(carg(z2) <= M_PI && carg(z2) >= -M_PI);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
