#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	/* We expect this trivial comparison to succeed. */
	assert(fabs(fminl(123.45, 234.56) - 123.45) < 0.01);

	/* If one argument is NaN, the other is returned. */
	assert(fabs(fminl(123.45, nan("")) - 123.45) < 0.01);
	assert(fabs(fminl(nan(""), 123.45) - 123.45) < 0.01);

	/* If both arguments are NaN, NaN shall be returned. */
	assert(isnan(fminl(nan(""), nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
