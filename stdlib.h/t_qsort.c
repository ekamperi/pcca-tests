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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NTHREADS	10	/* Number of threads to spawn */
#define	NITEMS		100000	/* Number of items to sort (per thread) */

/* Function prototypes. */
static void *thrfun(void *);
static int mycmp(const void *, const void *);

int main(void)
{
	pthread_t tid[NTHREADS];
	size_t i;

	/* Initialize random number generator. */
	srand(time(NULL));

	/* Create the threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&tid[i], NULL, thrfun, NULL) == 0);

	/* Wait for the threads to complete. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(tid[i], NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thrfun(void *arg)
{
	int a[NITEMS];
	size_t i;

	/* Generate some (not so) random numbers. */
	for (i = 0; i < NITEMS; i++)
		a[i] = rand();

	/* Sort the array. */
	qsort(a, NITEMS, sizeof(*a), mycmp);

	/* Validate the results. */
	for (i = 1; i < NITEMS; i++)
		assert(a[i] >= a[i-1]);

	pthread_exit(NULL);
}

static int
mycmp(const void *px, const void *py)
{
	int x = *(const int *)px;
	int y = *(const int *)py;

	return (x - y);
}
