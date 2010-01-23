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

struct tentry {
	double x;       /* Input */
	double y;       /* Log output */
} ttable[] = {
	{  0.017000, -4.074541 },
	{  2.017000,  0.701611 },
	{  4.073227,  1.404435 },
	{  6.151773,  1.816740 },
	{  8.245072,  2.109615 },
	{ 10.349474,  2.336935 },
	{ 12.462807,  2.522748 },
	{ 14.583620,  2.679899 },
	{ 16.710878,  2.816059 },
	{ 18.843802,  2.936184 },
	{ 20.981781,  3.043654 },
	{ 23.124330,  3.140885 },
	{ 25.271046,  3.229659 },
	{ 27.421596,  3.311330 },
	{ 29.575694,  3.386952 },
	{ 31.733098,  3.457360 },
	{ 33.893594,  3.523226 },
	{ 36.056997,  3.585100 },
	{ 38.223142,  3.643441 },
	{ 40.391882,  3.698628 },
	{ 42.563087,  3.750987 },
	{ 44.736638,  3.800792 },
	{ 46.912427,  3.848282 },
	{ 49.090356,  3.893662 },
	{ 51.270337,  3.937112 },
	{ 53.452286,  3.978789 },
	{ 55.636128,  4.018832 },
	{ 57.821794,  4.057365 },
	{ 60.009218,  4.094498 },
	{ 62.198339,  4.130328 },
	{ 64.389103,  4.164944 },
};

int
main(void)
{
	size_t i, N;

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++)
		assert(fabs(log(ttable[i].x) - ttable[i].y) < 0.001);

	/* Ix x is NaN, a NaN shall be returned. */
	assert(isnan(log(nan(""))) != 0);

	/* If x is 1, +0 shall be returned. */
	assert(fabs(log(1) - 0) < 0.001);
	assert(signbit(log(1)) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
