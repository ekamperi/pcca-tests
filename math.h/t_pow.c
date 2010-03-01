#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double x;       /* Input */
	double y;
	double z;	/* pow output */
	enum {
		NONE,
		SIGNED_ZERO
	} e;
} ttable[] = {
	/*
	 * For any value of y (including NaN), if x is +1,
	 * 1.0 shall be returned.
	 */
	{ +1,   0, 1.0, NONE },
	{ +1,  -1, 1.0, NONE },
	{ +1, NAN, 1.0, NONE },

	/*
	 * For any value of x (including NaN), if y is +-0,
	 * 1.0 shall be returned.
	 */
	{   1, +0.0, 1.0, NONE },
	{  -1, +0.0, 1.0, NONE },
	{   0, +0.0, 1.0, NONE },
	{ NAN, +0.0, 1.0, NONE },
        {   1, -0.0, 1.0, NONE },
        {  -1, -0.0, 1.0, NONE },
        {   0, -0.0, 1.0, NONE },
        { NAN, -0.0, 1.0, NONE },

	/*
	 * For any odd integer value of y > 0, if x is +-0,
	 * +-0 shall be returned.
	 */
	{ +0.0, 1, +0.0, SIGNED_ZERO },
	{ +0.0, 3, +0.0, SIGNED_ZERO },
        { -0.0, 1, -0.0, SIGNED_ZERO },
        { -0.0, 3, -0.0, SIGNED_ZERO },

	/*
	 * For y > 0 and not an odd integer, if x is +-0,
	 * +0 shall be returned.
	 */
	{ +0.0, 2, +0.0, SIGNED_ZERO },
        { +0.0, 4, +0.0, SIGNED_ZERO },
        { -0.0, 2, +0.0, SIGNED_ZERO },
        { -0.0, 4, +0.0, SIGNED_ZERO },

	/* If x is -1, and y is +-Inf, 1.0 shall be returned. */
	{ -1, +INFINITY, 1.0, NONE },
        { -1, +INFINITY, 1.0, NONE },
        { -1, -INFINITY, 1.0, NONE },
        { -1, -INFINITY, 1.0, NONE },

	/* For |x| < 1, if y is -Inf, +Inf shall be returned. */
	{ +0.0, -INFINITY, +INFINITY, NONE },
        { -0.0, -INFINITY, +INFINITY, NONE },
        { +0.5, -INFINITY, +INFINITY, NONE },
	{ -0.5, -INFINITY, +INFINITY, NONE },

	/* For |x| > 1, if y is -Inf, +0 shall be returned. */
        { +1.1, -INFINITY, +0.0, SIGNED_ZERO },
        { -1.1, -INFINITY, +0.0, SIGNED_ZERO },
        { +2.0, -INFINITY, +0.0, SIGNED_ZERO },
        { -2.0, -INFINITY, +0.0, SIGNED_ZERO },

	/* For |x| < 1, if y is +Inf, +0 shall be returned. */
	{ +0.0, +INFINITY, +0.0, SIGNED_ZERO },
	{ -0.0, +INFINITY, +0.0, SIGNED_ZERO },
        { +0.5, +INFINITY, +0.0, SIGNED_ZERO },
        { -0.5, +INFINITY, +0.0, SIGNED_ZERO },

	/* For |x| > 1, if y is +Inf, +Inf shall be returned. */
	{ +1.1, +INFINITY, +INFINITY, NONE },
	{ -1.1, +INFINITY, +INFINITY, NONE },
        { +2.0, +INFINITY, +INFINITY, NONE },
	{ -2.0, +INFINITY, +INFINITY, NONE },


};

int
main(void)
{
	size_t i, N;

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++) {
		if (fabs(pow(ttable[i].x, ttable[i].y) - ttable[i].z) > 0.001)
			printf("-> %d\n", i);

		if (ttable[i].e == SIGNED_ZERO) {
			assert(signbit(ttable[i].x, ttable[i].y) == signbit(ttable[i].z));
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
