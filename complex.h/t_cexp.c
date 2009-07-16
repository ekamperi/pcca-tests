#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Exp output */
} ttable[] = {
	{ 0.823 + 1.456*I, 0.260854 + 2.262333*I },
	{-1.005 + 1.210*I, 0.129221 + 0.342477*I },
	{ 0.587 - 0.967*I, 1.021185 - 1.480570*I },
	{-1.101 - 1.252*I, 0.104225 - 0.315783*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(cexp(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(cexp(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	/*
	 * Add an extra check based on the identity:
	 * cexp(I * z) = ccos(z) + I * csin(z)
	 */
	double rl, im;
	double complex z1, z2;
	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z1 =  cexp(I * (rl + im*I));
			z2 = ccos(rl + im*I) + I * csin(rl + im*I);
			assert(fabs(creal(z1) - creal(z2)) < 0.001);
			assert(fabs(cimag(z1) - cimag(z2)) < 0.001);
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
