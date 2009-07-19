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

int main(void)
{
	double rl, im;
	double complex z, w;
	int n;

	/*
	 * Solaris 10 libm's survives even larger values of n.
	 * Whereas {Net, DragonFly}BSD and glibc not.
	 */
	for (rl = -5.0; rl < 5.0; rl += 0.04) {
		for (im = -5.0; im < 5.0; im += 0.03) {
			for (n = -3; n < 3 ; n++) {
				/* Euler formula */
				z = cexp(I*n*(rl + im*I));
				w = ccos(n*(rl + im*I)) + I*csin(n*(rl + im*I));
				assert(fabs(creal(z) - creal(w)) < 0.001);
				assert(fabs(cimag(z) - cimag(w)) < 0.001);

				/* De Moivre formula */
				z = cpow(ccos(rl + im*I) + I*csin(rl + im*I), n);
				assert(fabs(creal(z) - creal(w)) < 0.001);
                                assert(fabs(cimag(z) - cimag(w)) < 0.001);
			}
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
