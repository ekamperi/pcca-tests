#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Cos output */
} ttable[] = {
	{ 1.123 + 2.456*I,  2.542430 - 5.215659*I },
	{-2.505 + 3.021*I, -8.266634 + 6.082219*I },
	{ 1.587 - 2.667*I, -0.117197 + 7.162687*I },
	{-3.101 - 0.552*I, -1.155308 - 0.023556*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(ccos(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(ccos(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
