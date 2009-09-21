#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double rv;

	/* If x is NaN, a NaN shall be returned. */
	rv = tgamma(nan(""));
	assert(isnan(rv) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
