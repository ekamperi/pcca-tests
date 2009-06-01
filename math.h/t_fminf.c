#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	/* We expect this trivial comparison to succeed. */
	assert(fabs(fminf(123.45, 234.56) - 123.45) < 0.01);

	/* If one argument is NaN, the other is returned. */
	assert(fabs(fminf(123.4, nan("")) - 123.4) < 0.01);
	assert(fabs(fminf(nan(""), 123.4) - 123.4) < 0.01);

	/* If both arguments are NaN, NaN shall be returned. */
	assert(isnan(fminf(nan(""), nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
