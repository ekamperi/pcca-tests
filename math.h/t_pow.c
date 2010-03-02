/*
 * Copyright (c) 2010, Stathis Kamperis
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define	CHK_REG		(1 << 0)
#define CHK_INF		(1 << 1)
#define CHK_SIGN	(1 << 2)

struct tentry {
	double x;       /* Input */
	double y;
	double z;	/* pow output */
	int check;
} ttable[] = {
	/*
	 * For any value of y (including NaN), if x is +1,
	 * 1.0 shall be returned.
	 */
	{ +1,   0, 1.0, CHK_REG },
	{ +1,  -1, 1.0, CHK_REG },
	{ +1, 101, 1.0, CHK_REG },
	{ +1, NAN, 1.0, CHK_REG },

	/*
	 * For any value of x (including NaN), if y is +-0,
	 * 1.0 shall be returned.
	 */
	{   1, +0.0, 1.0, CHK_REG },
	{  -1, +0.0, 1.0, CHK_REG },
	{   0, +0.0, 1.0, CHK_REG },
	{ NAN, +0.0, 1.0, CHK_REG },
        {   1, -0.0, 1.0, CHK_REG },
        {  -1, -0.0, 1.0, CHK_REG },
        {   0, -0.0, 1.0, CHK_REG },
        { NAN, -0.0, 1.0, CHK_REG },

	/*
	 * For any odd integer value of y > 0, if x is +-0,
	 * +-0 shall be returned.
	 */
	{ +0.0, 1, +0.0, CHK_REG | CHK_SIGN },
	{ +0.0, 3, +0.0, CHK_REG | CHK_SIGN },
        { -0.0, 1, -0.0, CHK_REG | CHK_SIGN },
        { -0.0, 3, -0.0, CHK_REG | CHK_SIGN },

	/*
	 * For y > 0 and not an odd integer, if x is +-0,
	 * +0 shall be returned.
	 */
	{ +0.0, 2, +0.0, CHK_REG | CHK_SIGN },
        { +0.0, 4, +0.0, CHK_REG | CHK_SIGN },
        { -0.0, 2, +0.0, CHK_REG | CHK_SIGN },
        { -0.0, 4, +0.0, CHK_REG | CHK_SIGN },

	/* If x is -1, and y is +-Inf, 1.0 shall be returned. */
	{ -1, +INFINITY, 1.0, CHK_REG },
        { -1, +INFINITY, 1.0, CHK_REG },
        { -1, -INFINITY, 1.0, CHK_REG },
        { -1, -INFINITY, 1.0, CHK_REG },

	/* For |x| < 1, if y is -Inf, +Inf shall be returned. */
	{ +0.0, -INFINITY, +INFINITY, CHK_INF | CHK_SIGN },
        { -0.0, -INFINITY, +INFINITY, CHK_INF | CHK_SIGN },
        { +0.5, -INFINITY, +INFINITY, CHK_INF | CHK_SIGN },
	{ -0.5, -INFINITY, +INFINITY, CHK_INF | CHK_SIGN },

	/* For |x| > 1, if y is -Inf, +0 shall be returned. */
        { +1.1, -INFINITY, +0.0, CHK_REG | CHK_SIGN },
        { -1.1, -INFINITY, +0.0, CHK_REG | CHK_SIGN },
        { +2.0, -INFINITY, +0.0, CHK_REG | CHK_SIGN },
        { -2.0, -INFINITY, +0.0, CHK_REG | CHK_SIGN },

	/* For |x| < 1, if y is +Inf, +0 shall be returned. */
	{ +0.0, +INFINITY, +0.0, CHK_REG | CHK_SIGN  },
	{ -0.0, +INFINITY, +0.0, CHK_REG | CHK_SIGN  },
        { +0.5, +INFINITY, +0.0, CHK_REG | CHK_SIGN  },
        { -0.5, +INFINITY, +0.0, CHK_REG | CHK_SIGN  },

	/* For |x| > 1, if y is +Inf, +Inf shall be returned. */
	{ +1.1, +INFINITY, +INFINITY, CHK_INF | CHK_SIGN },
	{ -1.1, +INFINITY, +INFINITY, CHK_INF | CHK_SIGN },
        { +2.0, +INFINITY, +INFINITY, CHK_INF | CHK_SIGN },
	{ -2.0, +INFINITY, +INFINITY, CHK_INF | CHK_SIGN },


	/* For y an odd integer < 0, if x is -Inf, -0 shall be returned. */
	{ -INFINITY, -1, -0.0, CHK_REG | CHK_SIGN },
        { -INFINITY, -3, -0.0, CHK_REG | CHK_SIGN },
        { -INFINITY, -5, -0.0, CHK_REG | CHK_SIGN },
        { -INFINITY, -7, -0.0, CHK_REG | CHK_SIGN },

	/*
	 * For y < 0 and not an odd integer, if x is -Inf,
	 * +0 shall be returned.
	 */
	{ -INFINITY, -2, +0.0, CHK_REG | CHK_SIGN },
        { -INFINITY, -4, +0.0, CHK_REG | CHK_SIGN },
        { -INFINITY, -6, +0.0, CHK_REG | CHK_SIGN },
        { -INFINITY, -8, +0.0, CHK_REG | CHK_SIGN },

	/* For y an odd integer > 0, if x is -Inf, -Inf shall be returned. */
	{ -INFINITY, 1, -INFINITY, CHK_INF | CHK_SIGN },
	{ -INFINITY, 3, -INFINITY, CHK_INF | CHK_SIGN },
        { -INFINITY, 5, -INFINITY, CHK_INF | CHK_SIGN },
        { -INFINITY, 7, -INFINITY, CHK_INF | CHK_SIGN },

	/*
	 * For y > 0 and not an odd integer, if x is -Inf,
	 * +Inf shall be returned.
	 */
	{ -INFINITY, 2, +INFINITY, CHK_INF | CHK_SIGN },
	{ -INFINITY, 4, +INFINITY, CHK_INF | CHK_SIGN },
        { -INFINITY, 6, +INFINITY, CHK_INF | CHK_SIGN },
        { -INFINITY, 8, +INFINITY, CHK_INF | CHK_SIGN },

	/* For y < 0, if x is +Inf, +0 shall be returned. */
        { +INFINITY, -1, +0.0, CHK_REG | CHK_SIGN },
	{ +INFINITY, -2, +0.0, CHK_REG | CHK_SIGN },
        { +INFINITY, -3, +0.0, CHK_REG | CHK_SIGN },
	{ +INFINITY, -4, +0.0, CHK_REG | CHK_SIGN },

	/* For y > 0, if x is +Inf, +Inf shall be returned. */
        { +INFINITY, 1, +INFINITY, CHK_INF | CHK_SIGN },
        { +INFINITY, 2, +INFINITY, CHK_INF | CHK_SIGN },
        { +INFINITY, 3, +INFINITY, CHK_INF | CHK_SIGN },
        { +INFINITY, 4, +INFINITY, CHK_INF | CHK_SIGN },

	/*
	 * For y an odd integer < 0, if x is +-0, a pole error shall occur and
	 * +-HUGE_VAL, +-HUGE_VALF, and +-HUGE_VALL shall be returned for pow(),
	 * powf(), and powl(), respectively.
	 */
        { +0.0, -1, +HUGE_VAL, CHK_INF | CHK_SIGN },
        { +0.0, -3, +HUGE_VAL, CHK_INF | CHK_SIGN },
        { -0.0, -1, -HUGE_VAL, CHK_INF | CHK_SIGN },
        { -0.0, -3, -HUGE_VAL, CHK_INF | CHK_SIGN },

	/*
	 * For y < 0 and not an odd integer, if x is +-0, a pole error shall
	 * occur and HUGE_VAL, HUGE_VALF, and HUGE_VALL shall be returned for
	 * pow(), powf(), and powl(), respectively.
	 */
        { +0.0, -2, HUGE_VAL, CHK_INF | CHK_SIGN },
        { +0.0, -4, HUGE_VAL, CHK_INF | CHK_SIGN },
        { -0.0, -2, HUGE_VAL, CHK_INF | CHK_SIGN },
        { -0.0, -4, HUGE_VAL, CHK_INF | CHK_SIGN },
};

int
main(void)
{
	size_t i, N;
	double oval;	/* output value */

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++) {
		/* Make sure that only allowed checks are set */
		assert((ttable[i].check & ~(CHK_REG | CHK_SIGN | CHK_INF))
		    == 0);

		/* Don't allow conflicting types to be set */
		assert((ttable[i].check & (CHK_REG | CHK_INF))
		    != (CHK_REG | CHK_INF));

		oval = pow(ttable[i].x, ttable[i].y);
		if (ttable[i].check & CHK_REG) {
			assert(fabs(oval - ttable[i].z) < 0.001);
		}
                if (ttable[i].check & CHK_INF) {
			assert(isinf(oval));
		}
		if (ttable[i].check & CHK_SIGN) {
			assert(signbit(oval) == signbit(ttable[i].z));
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
