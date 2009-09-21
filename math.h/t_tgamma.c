#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double x;       /* Input */
	double y;       /* Gamma output */
} ttable[] = {
	{ 1.000,    1.000 },
	{ 1.111,    0.947 },
	{ 3.000,    2.000 },
	{ 3.309,    2.708 },
	{ 5.000,   24.000 },
	{ 5.050,   25.881 },
	{ 7.000,  720.000 },
	{ 7.777, 3226.060 }
};

int main(void)
{
        size_t i;

        for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++)
                assert(fabs(tgamma(ttable[i].x) - ttable[i].y) < 0.01);

	/* If x is NaN, a NaN shall be returned. */
	double rv;

	rv = tgamma(nan(""));
	assert(isnan(rv) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
