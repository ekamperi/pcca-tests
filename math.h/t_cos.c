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

struct tentry {
	double x;       /* Input */
	double y;       /* cos output */
} ttable[] = {
	{   8.771900, -0.794338 },
	{  12.431900,  0.990972 },
	{  18.091900,  0.726448 },
	{  25.751900,  0.814366 },
	{  35.411900, -0.656685 },
	{  47.071900, -0.998648 },
	{  60.731900, -0.504805 },
	{  76.391900,  0.545612 },
	{  94.051900,  0.980876 },
	{ 113.711900,  0.817024 },
	{ 135.371900, -0.960105 },
	{ 159.031900, -0.372286 },
	{ 184.691900, -0.788723 },
	{ 212.351900,  0.290161 },
	{ 242.011899, -0.994036 },
	{ 273.671899, -0.938222 },
	{ 307.331900,  0.855552 },
	{ 342.991899, -0.848156 },
	{ 380.651900, -0.868221 },
	{ 420.311899,  0.789062 },
	{ 461.971899, -0.987578 }
};

int
main(void)
{
	size_t i, N;

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++)
		assert(fabs(cos(ttable[i].x) - ttable[i].y) < 0.001);

	/* Ix x is NaN, a NaN shall be returned. */
	assert(isnan(cos(nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
