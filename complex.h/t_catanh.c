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
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Don't be too harsh with symbols. */
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

struct tentry {
	double complex x;	/* Input */
	double complex y;	/* Arc hyperbolic tan output */
} ttable[] = {
	{ 1.123 + 2.456*I,  0.138878 + 1.239414*I },
	{-2.505 + 3.021*I, -0.157765 + 1.372177*I },
	{ 1.587 - 2.667*I,  0.153962 - 1.294031*I },
	{-3.101 - 1.552*I, -0.259006 - 1.433576*I }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++) {
		/* Compare real parts. */
		assert(fabs(creal(catanh(ttable[i].x)) - creal(ttable[i].y))
		    < 0.001);

		/* Compare imaginary parts. */
		assert(fabs(cimag(catanh(ttable[i].x)) - cimag(ttable[i].y))
		    < 0.001);
	}

	/*
	 * The result is in the range [-ipi/2, +ipi/2] along the imaginary axis.
	 */
	double rl, im;
	double complex z;

	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z = catanh(rl + im*I);
			assert(fabs(cimag(z)) - M_PI_2 < 0.00001);
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
