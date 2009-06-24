#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Arc Cos output */
} ttable[] = {
	{ 1.123 + 2.456*I, 1.166190 - 1.709185*I },
	{-2.505 + 3.021*I, 2.247292 - 2.063744*I },
	{ 1.587 - 2.667*I, 1.055989 + 1.838540*I },
	{-3.101 - 0.552*I, 2.956068 + 1.816065*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(cacos(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(cacos(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	/*
	 * The result across the real axis is in the range [0, +pi].
	 */
	double rl, im;
	double complex z;

	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z =  cacos(rl + im*I);
			assert(creal(z) >= 0.0);
			assert(creal(z) <= M_PI);
		}
        }

	printf("passed\n");

	return (EXIT_SUCCESS);
}
