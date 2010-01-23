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
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct tentry {
	double x;       /* Input */
	double y;       /* Gamma output */
} ttable[] = {
	{  1.000000,   1.000000 },
	{  5.965924, 113.234400 },
	{  5.283818,  37.123551 },
	{  4.659137,  14.554014 },
	{  4.080038,   6.640580 },
	{  3.538967,   3.470194 },
	{  3.030652,   2.057758 },
	{  2.551185,   1.378934 },
	{  2.097548,   1.045243 },
	{  1.667331,   0.902854 },
	{  1.258566,   0.904677 },
	{  0.869609,   1.094417 },
	{  0.499068,   1.775704 },
	{  0.145745,   6.411584 },
	{ -0.191398,  -6.032989 },
	{ -0.513276,  -3.545983 },
	{ -0.820697,  -6.278702 },
	{ -1.114382,   8.476865 },
	{ -1.394979,   2.682064 },
	{ -1.663072,   2.402314 },
	{ -1.919193,   6.730035 },
	{ -2.163827,  -2.729105 },
	{ -2.397417,  -1.114067 },
	{ -2.620372,  -0.888588 },
	{ -2.833069,  -1.284476 },
	{ -3.035859,   4.451698 },
	{ -3.229064,   0.591448 },
	{ -3.412989,   0.316233 },
	{ -3.587915,   0.248223 },
	{ -3.754107,   0.269779 },
	{ -3.911813,   0.546090 },
	{ -4.061268,  -0.623712 }
};

int
main(void)
{
	size_t i, N;

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++)
		assert(fabs(tgamma(ttable[i].x) - ttable[i].y) < 0.001);

	/* If x is NaN, a NaN shall be returned. */
	assert(isnan(tgamma(nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
