#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Sine output */
} ttable[] = {
	{ 1.123 + 2.456*I,  5.292979 + 2.505290*I },
	{-2.505 + 3.021*I, -6.111200 - 8.227431*I },
	{ 1.587 - 2.667*I,  7.232138 + 0.116072*I },
	{-3.101 - 0.552*I, -0.046923 + 0.579985*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(csin(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(csin(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
