#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        double rl, im;
        double complex z;

        for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z = rl + im*I;
			assert(fabs(creal(z) - rl) < 0.00001);
		}
        }

	printf("passed\n");

	return (EXIT_SUCCESS);
}
