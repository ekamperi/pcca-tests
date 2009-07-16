/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.

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
	double complex z;
	size_t i;

	/*
	 * If the complex number doesn't have any infinite parts,
	 * then cproj() projects the number to itself.
	 *
	 * Funny quote from the cproj(3) man page in Linux, as of 16/09/2009:
	 * CONFORMING TO: C99
	 * NOTES: The glibc implementation is broken and does something entirely
	 * different.
	 *
	 * But neither the man page nor any comments in code say what it actually
	 * does. Anyway, after some digging I found that it does a stereographic
	 * projection from the complex plane to a unitary sphere in R^3. The new
	 * complex number is 2x/(x^2+y^2+1) + I2y/(x^2+y^2+1).
	 */
	for (rl = -10.0; rl < 10.0; rl += 0.04) {
		for (im = -10.0; im < 10.0; im += 0.03) {
			z = clog(rl + im*I);
			assert(fabs(creal(cproj(z)) - creal(z)) < 0.001);
			assert(fabs(cimag(cproj(z)) - cimag(z)) < 0.001);
		}
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
