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

/* Don't be too harsh with symbols. */
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

int main(void)
{
	double x, y, s;

	for (x = -10.0; x < 10.0; x += 0.1) {
		/* Symmetry */
		assert(fabs(sin(-x) + sin(x)) < 0.001);
		assert(fabs(cos(-x) - cos(x)) < 0.001);

		/* Shifts and periodicity */
		assert(fabs(sin(x + M_PI_2) - cos(x)) < 0.001);
		assert(fabs(cos(x + M_PI_2) + sin(x)) < 0.001);

		/* Angle sum and difference */
		for (y = -10; y < 10.0; y += 0.01) {
			s = sin(x) * cos(y) + cos(x) * sin(y);
			assert(fabs(sin(x+y) - s) < 0.001);

			s = sin(x) * cos(y) - cos(x) * sin(y);
			assert(fabs(sin(x-y) - s) < 0.001);

			s = cos(x) * cos(y) + sin(x) * sin(y);
			assert(fabs(cos(x-y) - s) < 0.001);

			s = cos(x) * cos(y) + sin(x) * sin(y);
			assert(fabs(cos(x-y) - s) < 0.001);
		}

		/* Half, double, triple angle */
		assert(fabs(sin(x/2)*sin(x/2) - 0.5*(1-cos(x))) < 0.001);
		assert(fabs(cos(x/2)*cos(x/2) - 0.5*(1+cos(x))) < 0.001);

		assert(fabs(sin(2*x) - 2*sin(x)*cos(x)) < 0.001);
		assert(fabs(cos(2*x) - (cos(x)*cos(x) - sin(x)*sin(x)))
		    < 0.001);

		assert(fabs(sin(3*x) - (3*sin(x) - 4*sin(x)*sin(x)*sin(x)))
		    < 0.001);
		assert(fabs(cos(3*x) - (4*cos(x)*cos(x)*cos(x) - 3*cos(x)))
		    < 0.001);

		/* Product to sum */
		for (y = -10.0; y < 10.0; y += 0.01) {
			s = 0.5*(cos(x-y) + cos(x + y));
			assert(fabs(cos(x)*cos(y) - s) < 0.001);

			s = 0.5*(cos(x-y) - cos(x+y));
			assert(fabs(sin(x)*sin(y) - s) < 0.001);

			s = 0.5*(sin(x+y) + sin(x-y));
			assert(fabs(sin(x)*cos(y) - s) < 0.001);

			s = 0.5*(sin(x+y) - sin(x-y));
			assert(fabs(cos(x)*sin(y) - s) < 0.001);
		}

		s = sin(x) * sin(x) + cos(x) * cos(x);
		assert(fabs(s - 1) < 0.001);

		/* XXX: Power reduction ? */
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
