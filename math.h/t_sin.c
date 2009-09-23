#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double x;       /* Input */
	double y;       /* rint output */
} ttable[] = {
	/* If x is +/-0, x shall be returned. */
	{ +0.0, +0.0 },
	{ -0.0, -0.0 }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++)
		assert(fabs(rint(ttable[i].x) - ttable[i].y) < 0.001);

	/* Ix x is NaN, a NaN shall be returned. */
	assert(isnan(sin(nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
