/*
 * Copyright (c) 2009, Stathis Kamperis
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

int main(void)
{
	float xf;
	double xd;
	long double xld;

	/*
	 * 7.12.3.6
	 * NaNs, zeros, and infinities have a sign bit.
	 * As usual we aren't too harsh regarding symbols' definitions.
	 * Their availability is checked by symgen.pl.
	 */
#ifdef	NAN
	xf = NAN;	(void)signbit(xf);
	xd = NAN;	(void)signbit(xd);
	xld = NAN;	(void)signbit(xld);
#endif	/* ! NAN */

	/* If zero is unsigned, it is treated as positive. */
	xf = 0.0;	assert(signbit(xf) == 0);
	xd = 0.0;	assert(signbit(xd) == 0);
	xld = 0.0;	assert(signbit(xld) == 0);

	xf = -0.0;	assert(signbit(xf) != 0);
	xd = -0.0;	assert(signbit(xd) != 0);
	xld = -0.0;	assert(signbit(xld) != 0);

	/* INFINITY expands to a positive expression. */
#ifdef INFINITY
	xf = INFINITY;	assert(signbit(xf) == 0);
	xd = INFINITY;	assert(signbit(xd) == 0);
	xld = INFINITY;	assert(signbit(xld) == 0);
#endif	/* ! INFINITY */

	/*
	 * 7.1.2.3
	 * The following constants, if available, are all positive.
	 */
#ifdef	HUGE_VAL
	xd = HUGE_VAL;
	assert(signbit(xld) == 0);
#endif	/* ! HUGE_VAL */

#ifdef	HUGE_VALF
	xf = HUGE_VALF;
	assert(signbit(xf) == 0);
#endif	/* ! HUGE_VALF */

#ifdef	HUGE_VALL
	xld = HUGE_VALL;
	assert(signbit(xld) == 0);
#endif	/* ! HUVE_VALL */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
