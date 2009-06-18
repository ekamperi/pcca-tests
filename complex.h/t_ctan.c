#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Tan output */
} ttable[] = {
	{ 7.123 + 1.456*I,  0.109056 + 1.005952*I },
	{-3.505 + 0.021*I, -0.380106 + 0.024032*I },
	{ 4.587 - 0.667*I,  0.233871 - 1.664692*I },
	{-1.101 - 1.552*I, -0.076336 - 1.051556*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(ctan(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(ctan(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
