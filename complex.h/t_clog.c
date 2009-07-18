#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Don't be too harsh with symbols. */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif /* !M_PI */

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Log output */
} ttable[] = {
	{ 7.123 + 1.456*I, 1.983796 + 0.201631*I },
	{-3.505 + 1.210*I, 1.310488 + 2.809182*I },
	{ 4.587 - 0.667*I, 1.533688 - 0.144399*I },
	{-1.101 - 1.552*I, 0.643362 - 2.187808*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(clog(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(clog(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	/*
	 * The result is in the [-ipi, +ipi] interval,
	 * along the imaginary axis.
	 */
	double rl, im;
	double complex z;
	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z =  clog(rl + im*I);
			assert(cabs(cimag(z)) <=  M_PI);
			assert(cabs(cimag(z)) >= -M_PI);
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
