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
#include <unistd.h>	/* for sleep(3) */

#define NTHREADS	10

pthread_spinlock_t lock1;	/* level-1 lock */
pthread_spinlock_t lock2;	/* level-2 lock */

/* Function prototypes. */
static void *thread1(void *);
static void *thread2(void *);

int cnt11 = 0;	/* level-1, counter 1 -- increases monotonically */
int cnt12 = 0;	/* level-1, counter 2 */
int cnt21 = 0;	/* level-2, counter 1 -- incrases monotonically */
int cnt22 = 0;	/* level-2, counter 2 */

int main(void)
{
	pthread_t thpool[NTHREADS];
	size_t i;

	/* Initialize level-1 spinlock. */
	assert(pthread_spin_init(&lock1, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Acquire level-1 spinlock. */
	assert(pthread_spin_lock(&lock1) == 0);

	/* Create level-1 threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&thpool[i], NULL, thread1, (void *)NULL)
		    == 0);

	/* Sleep so that level-1 threads spin a bit. */
	sleep(1);

	/* Enough is enough -- release level-1 spinlock. */
	assert(pthread_spin_unlock(&lock1) == 0);

	/*
	 * Wait for level-1 threads to complete.
	 * Each level-1 thread acquires the level-1 spinlock, so the rest will
	 * spin again a bit.
	 */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Destroy level-1 spinlock. */
	assert(pthread_spin_destroy(&lock1) == 0);

	/* Make sure that `NTHREADS' level-1 threads ran. */
	assert(cnt11 == NTHREADS);
	assert(cnt12 == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread1(void *arg)
{
	pthread_t thpool[NTHREADS];
	size_t i;

        /* Acquire level-1 spinlock. */
        assert(pthread_spin_lock(&lock1) == 0);

	/* Increase monotonically. */
	cnt11++;

	/* Counter must be 0. */
	assert(cnt12 == 0);

	cnt12++;
	cnt12--;

	assert(cnt12 == 0);

	/* Initialize counter. */
	cnt21 = 0;

	/* Initialize level-2 spinlock. */
	assert(pthread_spin_init(&lock2, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Create level-2 threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&thpool[i], NULL, thread2, (void *)NULL)
		    == 0);

	/*
	 * Wait for level-2 threads to complete.
	 * Each level-2 thread acquires the level-2 spinlock, so the rest will
	 * spin again a bit.
	 */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Release level-2 spinlock. */
	assert(pthread_spin_unlock(&lock2) == 0);

	/* Destroy level-2 spinlock. */
	assert(pthread_spin_destroy(&lock2) == 0);

	/* Release level-1 spinlock. */
	assert(pthread_spin_unlock(&lock1) == 0);

        /* Make sure that `NTHREADS' level-2 threads ran. */
        assert(cnt21 == NTHREADS);
	assert(cnt22 == 0);

	pthread_exit(NULL);
}


static void *
thread2(void *arg)
{
	/* Acquire level-2 spinlock. */
	assert(pthread_spin_lock(&lock2) == 0);

	/* Increase monotonically. */
	cnt21++;

	/* Counter must always be 0. */
	assert(cnt22 == 0);

	cnt22++;
	cnt22--;

	assert(cnt22 == 0);

	/* Release level-2 spinlock. */
	assert(pthread_spin_unlock(&lock2) == 0);

	pthread_exit(NULL);
}
