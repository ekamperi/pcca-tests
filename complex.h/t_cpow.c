#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input x */
	double complex y;	/* Input y */
	double complex z;	/* Pow output */
} ttable[] = {
	{ 2.123 + 1.456*I, 1.383796 + 0.201631*I, 1.708622 + 2.797664*I},
	{-0.605 + 6.110*I, 1.310488 + 2.809182*I, 0.053312 + 0.083538*I},
	{ 2.587 - 0.667*I, 1.533688 - 0.144399*I, 3.757550 - 2.196046*I},
	{-0.501 - 9.552*I, 0.643362 - 2.187808*I, 0.117221 + 0.036073*I}
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(cpow(ttable[i].x, ttable[i].y)) -
			creal(ttable[i].z)) < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(cpow(ttable[i].x, ttable[i].y)) -
			cimag(ttable[i].z))  < 0.001);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
