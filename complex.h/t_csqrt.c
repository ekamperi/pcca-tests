#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Sqrt output */
} ttable[] = {
	{ 7.123 + 1.456*I, 2.682656 + 0.271373*I },
	{-3.505 + 1.210*I, 0.318576 + 1.899076*I },
	{ 4.587 - 0.667*I, 2.147352 - 0.155308*I },
	{-1.101 - 1.552*I, 0.633193 - 1.225534*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(csqrt(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(csqrt(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}


	/*
	 * The result is in the range of the right half-plane,
	 * including the imaginary axis.
	 */
	double rl, im;
	double complex z;

	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z =  csqrt(rl + im*I);
			assert(creal(z) >= 0.0);
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
