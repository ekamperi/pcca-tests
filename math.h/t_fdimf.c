#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/* We expect this simple call to succeed. */
	assert(fabs(fdimf(200.00, 150.00) - 50.00) < 0.01);

	/* If one of the arguments is NaN, NaN is returned. */
	assert(isnan(fdimf(nan(""), 123.45)) != 0);
	assert(isnan(fdimf(123.45, nan(""))) != 0);

	/* If x-y < 0 and none of the arguments is Nan, +0 is returned. */
	assert(fabs(fdimf(150.00, 200.00)) < 0.01 &&
	       signbit(fdimf(150.00, 200.00)) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
