#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double rl, im;
	double complex z;
	size_t i;

	/*
	 * If the complex number doesn't have any infinite parts,
	 * then it projects to itself.
	 */
	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z = clog(rl + im*I);
			assert(fabs(creal(cproj(z)) - creal(z)) < 0.001);
			assert(fabs(cimag(cproj(z)) - cimag(z)) < 0.001);
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
