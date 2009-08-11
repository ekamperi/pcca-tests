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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int rv_pbst = 0;	/* Whether PTHREAD_BARRIER_SERIAL_THREAD was returned.*/
int rv_zero = 0;	/* Whether zero was returned. */

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_barrier_t pb;
	pthread_t th1, th2;

	/* Initialize barrier. */
	assert(pthread_barrier_init(&pb, NULL, 2) == 0);

	/* Create threads. */
	assert(pthread_create(&th1, NULL, thread, (void *)&pb) == 0);
	assert(pthread_create(&th2, NULL, thread, (void *)&pb) == 0);

	/* Wait for threads to complete. */
	assert(pthread_join(th1, NULL) == 0);
	assert(pthread_join(th2, NULL) == 0);

	/* Destroy barrier. */
	assert(pthread_barrier_destroy(&pb) == 0);

	/*
	 * PTHREAD_BARRIER_SERIAL_THREAD should be returned to one thread and
	 * zero to the other (but we don't know which one gets what).
	 */
	assert(rv_pbst == 1 && rv_zero == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	pthread_barrier_t *pb;
	int rv;

	/*
	 * Retrieve reference to the original barrier.
	 *
	 * Don't be tempted to dereference `arg' and get a copy of the barrier.
	 * The result of calling pthread_barrier_wait() on the copy will be
	 * undefined.
	 */
	pb = (pthread_barrier_t *)arg;

	/* This will block us. */
	rv = pthread_barrier_wait(pb);
	if (rv == PTHREAD_BARRIER_SERIAL_THREAD)
		rv_pbst = 1;
	else if (rv == 0)
		rv_zero = 1;

	pthread_exit(NULL);
}
