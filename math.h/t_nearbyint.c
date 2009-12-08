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
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	int inexacttest = 0;	/* skipped */

	/*
	 * The nearbyint*() functions shouldn't raise the inexact exception.
	 * Clear it now, so that we can check if it was raised later on.
	 */
#if defined(math_errhandling) && defined(MATH_ERREXCEPT) && \
        (math_errhandling & MATH_ERREXCEPT)
	feclearexcept(FE_INEXACT);
	inexacttest = 1;
#endif

	/* If x is NaN, a NaN shall be returned. */
	assert(isnan(nearbyint(nan(""))) != 0);

	/*
	 * If x is +/-0, +/-0 shall be returned.
	 *
	 * Don't use integers as they are promoted to float/double types,
	 * but they lose their signedness in the process.
	 */
	assert(signbit(nearbyint(+0.0)) == 0);
	assert(signbit(nearbyint(-0.0)) != 0);

	/* If x is ±Inf, x shall be returned. */
#ifdef INFINITY
	double x;

	x = +INFINITY;
	assert(isinf(nearbyint(x)) && signbit(x) == 0);

	x = -INFINITY;
	assert(isinf(nearbyint(x)) && signbit(x) != 0);
#endif

#if defined(math_errhandling) && defined(MATH_ERREXCEPT) && \
        (math_errhandling & MATH_ERREXCEPT)
	assert(fetestexcept(FE_INEXACT) == 0);
#endif

	printf("passed%s\n", inexacttest == 0 ?
	    " (inexact exception test skipped)" : "");

	return (EXIT_SUCCESS);
}
