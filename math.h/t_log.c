#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double x;       /* Input */
	double y;       /* Log output */
} ttable[] = {
	/* XXX: Add pair values */
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++)
		assert(fabs(rint(ttable[i].x) - ttable[i].y) < 0.001);

	/* Ix x is NaN, a NaN shall be returned. */
	assert(isnan(log(nan(""))) != 0);

	/* If x is 1, +0 shall be returned. */
	assert(fabs(log(1) - 0) < 0.001);
	assert(signbit(log(1)) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
