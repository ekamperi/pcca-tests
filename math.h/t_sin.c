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
	double y;       /* sin output */
} ttable[] = {
	{  -19.902800, -0.869032 },
	{  -16.642800,  0.804502 },
	{   -9.382800, -0.041965 },
	{    1.877199,  0.953424 },
	{   17.137200, -0.989997 },
	{   36.397200, -0.964067 },
	{   59.657200,  0.033054 },
	{   86.917200, -0.866123 },
	{  118.177200, -0.933237 },
	{  135.371900, -0.279636 },
	{  159.031900,  0.928118 },
	{  184.691900,  0.614748 },
	{  212.351900, -0.956977 },
	{  242.011899, -0.109048 },
	{  273.671899, -0.346032 },
	{  307.331900, -0.517716 },
	{  342.991899, -0.529745 },
	{  380.651900, -0.496176 },
	{  420.311899, -0.614313 },
	{  461.971899, -0.157126 },
};

int
main(void)
{
	size_t i, N;

	N = sizeof(ttable) / sizeof(struct tentry);
	for (i = 0; i < N; i++)
		assert(fabs(sin(ttable[i].x) - ttable[i].y) < 0.001);

	/* Ix x is NaN, a NaN shall be returned. */
	assert(isnan(sin(nan(""))) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
