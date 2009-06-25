#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Arc Sine output */
} ttable[] = {
	{ 1.123 + 2.456*I,  0.404607 + 1.709185*I },
	{-2.505 + 3.021*I, -0.676495 + 2.063744*I },
	{ 1.587 - 2.667*I,  0.514808 - 1.838540*I },
	{-3.101 - 0.552*I, -1.385271 - 1.816065*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(casin(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(casin(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	/*
	 * The result across the real axis is in the range [-pi/2, +pi/2].
	 */
	double rl, im;
	double complex z;

	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z =  casin(rl + im*I);
			assert(creal(z) >= -M_PI_2);
			assert(creal(z) <=  M_PI_2);
		}
        }

	printf("passed\n");

	return (EXIT_SUCCESS);
}