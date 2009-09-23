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

/*
 * The rint*() functions return the integral value (represented as a
 * double) nearest x in the direction of the current rounding mode.
 *
 * POSIX says that the rounding mode is implementation-defined, so
 * that leaves us in the dark, I guess.
 */

struct tentry {
	double x;       /* Input */
	double y;       /* rint output */
} ttable[] = {
	{   1.010,     1.000 },
	{  -1.010,    -1.000 },
	{   2.411,     2.000 },
	{  -2.411,    -2.000 },
	{   3.999,     4.000 },
	{  -3.999,    -4.000 },
	{   9.997,    10.000 },
	{  -9.997,   -10.000 },
	{  101.005,  101.000 },
	{ -101.005, -101.000 },
	{  507.777,  508.000 },
	{ -507.777, -508.000 }
};

int main(void)
{
	size_t i;

	for (i = 0; i < sizeof(ttable) / sizeof(struct tentry); i++)
		assert(fabs(rint(ttable[i].x) - ttable[i].y) < 0.001);

	/* If x is NaN, a NaN shall be returned. */
	assert(isnan(rint(nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
