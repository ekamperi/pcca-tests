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
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS	20
#define NITER		20

/* Function prototypes. */
static void *parent(void *arg);
static void *child(void *arg);

int
main(void)
{
	pthread_t thpool[NTHREADS];
	size_t i;

	/* Create parent threads. */
	for (i = 0; i < NTHREADS; i++)
                assert(pthread_create(&thpool[i], NULL, parent,
			   (void *)NULL) == 0);

	/* Wait for parent threads to complete. */
        for (i = 0; i < NTHREADS; i++)
                assert(pthread_join(thpool[i], NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
parent(void *arg)
{
	pthread_t thpool[NTHREADS];
	sem_t mysem;
	size_t i;

	/* Initialize semaphore. */
        assert(sem_init(&mysem,
                   0 /* not shared between processes */,
                   NTHREADS/2 /* semaphore value */) == 0);

        /* Create children threads. */
        for (i = 0; i < NTHREADS; i++)
                assert(pthread_create(&thpool[i], NULL, child,
                           (void *)&mysem) == 0);

        /* Wait for children threads to complete. */
        for (i = 0; i < NTHREADS; i++)
                assert(pthread_join(thpool[i], NULL) == 0);

	/* Destroy semaphore. */
	assert(sem_destroy(&mysem) == 0);

	pthread_exit(NULL);
}

static void *
child(void *arg)
{
	sem_t mysem;
	size_t i;

	/* Retrieve semaphore. */
	mysem = *(sem_t *)arg;

	for (i = 0; i < NITER; i++) {
		assert(sem_wait(&mysem) == 0);
		assert(sem_post(&mysem) == 0);
	}

	pthread_exit(NULL);
}
