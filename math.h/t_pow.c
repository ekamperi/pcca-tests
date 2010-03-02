#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define	CHK_NONE	(1 << 0)
#define CHK_SIGN	(1 << 1)
#define CHK_INF		(1 << 2)

struct tentry {
	double x;       /* Input */
	double y;
	double z;	/* pow output */
	int exchk;
} ttable[] = {
	/*
	 * For any value of y (including NaN), if x is +1,
	 * 1.0 shall be returned.
	 */
	{ +1,   0, 1.0, CHK_NONE },
	{ +1,  -1, 1.0, CHK_NONE },
	{ +1, 101, 1.0, CHK_NONE },
	{ +1, NAN, 1.0, CHK_NONE },

	/*
	 * For any value of x (including NaN), if y is +-0,
	 * 1.0 shall be returned.
	 */
	{   1, +0.0, 1.0, CHK_NONE },
	{  -1, +0.0, 1.0, CHK_NONE },
	{   0, +0.0, 1.0, CHK_NONE },
	{ NAN, +0.0, 1.0, CHK_NONE },
        {   1, -0.0, 1.0, CHK_NONE },
        {  -1, -0.0, 1.0, CHK_NONE },
        {   0, -0.0, 1.0, CHK_NONE },
        { NAN, -0.0, 1.0, CHK_NONE },

	/*
	 * For any odd integer value of y > 0, if x is +-0,
	 * +-0 shall be returned.
	 */
	{ +0.0, 1, +0.0, CHK_SIGN },
	{ +0.0, 3, +0.0, CHK_SIGN },
        { -0.0, 1, -0.0, CHK_SIGN },
        { -0.0, 3, -0.0, CHK_SIGN },

	/*
	 * For y > 0 and not an odd integer, if x is +-0,
	 * +0 shall be returned.
	 */
	{ +0.0, 2, +0.0, CHK_SIGN },
        { +0.0, 4, +0.0, CHK_SIGN },
        { -0.0, 2, +0.0, CHK_SIGN },
        { -0.0, 4, +0.0, CHK_SIGN },

	/* If x is -1, and y is +-Inf, 1.0 shall be returned. */
	{ -1, +INFINITY, 1.0, CHK_NONE },
        { -1, +INFINITY, 1.0, CHK_NONE },
        { -1, -INFINITY, 1.0, CHK_NONE },
        { -1, -INFINITY, 1.0, CHK_NONE },

	/* For |x| < 1, if y is -Inf, +Inf shall be returned. */
	{ +0.0, -INFINITY, +INFINITY, CHK_NONE },
        { -0.0, -INFINITY, +INFINITY, CHK_NONE },
        { +0.5, -INFINITY, +INFINITY, CHK_NONE },
	{ -0.5, -INFINITY, +INFINITY, CHK_NONE },

	/* For |x| > 1, if y is -Inf, +0 shall be returned. */
        { +1.1, -INFINITY, +0.0, CHK_SIGN },
        { -1.1, -INFINITY, +0.0, CHK_SIGN },
        { +2.0, -INFINITY, +0.0, CHK_SIGN },
        { -2.0, -INFINITY, +0.0, CHK_SIGN },

	/* For |x| < 1, if y is +Inf, +0 shall be returned. */
	{ +0.0, +INFINITY, +0.0, CHK_SIGN  },
	{ -0.0, +INFINITY, +0.0, CHK_SIGN  },
        { +0.5, +INFINITY, +0.0, CHK_SIGN  },
        { -0.5, +INFINITY, +0.0, CHK_SIGN  },

	/* For |x| > 1, if y is +Inf, +Inf shall be returned. */
	{ +1.1, +INFINITY, +INFINITY, CHK_SIGN | CHK_INF },
	{ -1.1, +INFINITY, +INFINITY, CHK_SIGN | CHK_INF },
        { +2.0, +INFINITY, +INFINITY, CHK_SIGN | CHK_INF },
	{ -2.0, +INFINITY, +INFINITY, CHK_SIGN | CHK_INF },


	/* For y an odd integer < 0, if x is -Inf, -0 shall be returned. */
	{ -INFINITY, -1, -0.0, CHK_SIGN },
        { -INFINITY, -3, -0.0, CHK_SIGN },
        { -INFINITY, -5, -0.0, CHK_SIGN },
        { -INFINITY, -7, -0.0, CHK_SIGN },

	/* For y < 0 and not an odd integer, if x is -Inf, +0 shall be returned. */
	{ -INFINITY, -2, +0.0, CHK_SIGN },
        { -INFINITY, -4, +0.0, CHK_SIGN },
        { -INFINITY, -6, +0.0, CHK_SIGN },
        { -INFINITY, -8, +0.0, CHK_SIGN },

	/* For y an odd integer > 0, if x is -Inf, -Inf shall be returned. */
	{ -INFINITY, 1, -INFINITY, CHK_SIGN | CHK_INF },
	{ -INFINITY, 3, -INFINITY, CHK_SIGN | CHK_INF },
        { -INFINITY, 5, -INFINITY, CHK_SIGN | CHK_INF },
        { -INFINITY, 7, -INFINITY, CHK_SIGN | CHK_INF },

	/* For y > 0 and not an odd integer, if x is -Inf, +Inf shall be returned. */
	{ -INFINITY, 1, -INFINITY, CHK_SIGN | CHK_INF },
	{ -INFINITY, 3, -INFINITY, CHK_SIGN | CHK_INF },
        { -INFINITY, 5, -INFINITY, CHK_SIGN | CHK_INF },
        { -INFINITY, 7, -INFINITY, CHK_SIGN | CHK_INF },

	/* For y < 0, if x is +Inf, +0 shall be returned. */
        { +INFINITY, -1, +0.0, CHK_SIGN },
	{ +INFINITY, -2, +0.0, CHK_SIGN },
        { +INFINITY, -3, +0.0, CHK_SIGN },
	{ +INFINITY, -4, +0.0, CHK_SIGN },

	/* For y > 0, if x is +Inf, +Inf shall be returned. */
        { +INFINITY, 1, +INFINITY, CHK_SIGN | CHK_INF },
        { +INFINITY, 2, +INFINITY, CHK_SIGN | CHK_INF },
        { +INFINITY, 3, +INFINITY, CHK_SIGN | CHK_INF },
        { +INFINITY, 4, +INFINITY, CHK_SIGN | CHK_INF },

	/*
	 * For y an odd integer < 0, if x is +-0, a pole error shall occur and
	 * +-HUGE_VAL, +-HUGE_VALF, and +-HUGE_VALL shall be returned for pow(),
	 * powf(), and powl(), respectively.
	 */
        { +0.0, -1, +HUGE_VAL, CHK_SIGN | CHK_INF },
        { +0.0, -3, +HUGE_VAL, CHK_SIGN | CHK_INF },
        { -0.0, -1, -HUGE_VAL, CHK_SIGN | CHK_INF },
        { -0.0, -3, -HUGE_VAL, CHK_SIGN | CHK_INF },

	/*
	 * For y < 0 and not an odd integer, if x is +-0, a pole error shall occur
	 * and HUGE_VAL, HUGE_VALF, and HUGE_VALL shall be returned for pow(),
	 * powf(), and powl(), respectively.
	 */
        { +0.0, -2, HUGE_VAL, CHK_SIGN | CHK_INF },
        { +0.0, -4, HUGE_VAL, CHK_SIGN | CHK_INF },
        { -0.0, -2, HUGE_VAL, CHK_SIGN | CHK_INF },
        { -0.0, -4, HUGE_VAL, CHK_SIGN | CHK_INF },
};

int
main(void)
{
	size_t i, N;
	double oval;	/* output value */

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++) {
		/* Paranoia */
		assert((ttable[i].exchk & ~(CHK_NONE | CHK_SIGN | CHK_INF)) == 0);

		oval = pow(ttable[i].x, ttable[i].y);
		assert((fabs(oval - ttable[i].z) < 0.001)
		    || (isnan(fabs(oval - ttable[i].z)) && (ttable[i].exchk & CHK_INF)));

		/* Execute any extra checks */
		if (ttable[i].exchk & CHK_SIGN) {
			assert(signbit(oval) == signbit(ttable[i].z));
		}
		if (ttable[i].exchk & CHK_INF) {
			assert(isinf(oval));
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
