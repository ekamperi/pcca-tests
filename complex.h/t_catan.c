#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Arc Cos output */
} ttable[] = {
	{ 1.123 + 2.456*I,  1.399392 + 0.340602*I },
	{-2.505 + 3.021*I, -1.403403 + 0.193275*I },
	{ 1.587 - 2.667*I,  1.394608 - 0.275800*I },
	{-3.101 - 1.552*I, -1.314585 - 0.121492*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(catan(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(catan(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	/*
	 * The result across the real axis is in the range [-pi/2, +pi/2].
	 */
	double rl, im;
	double complex z;

	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z =  catan(rl + im*I);
			assert(creal(z) >= -M_PI_2);
			assert(creal(z) <=  M_PI_2);
		}
        }

	printf("passed\n");

	return (EXIT_SUCCESS);
}
