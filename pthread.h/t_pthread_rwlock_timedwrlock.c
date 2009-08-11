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
#include <time.h>
#include <sys/time.h>

pthread_rwlock_t rwl;

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t tid;

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire read lock. */
	assert(pthread_rwlock_rdlock(&rwl) == 0);
	assert(pthread_rwlock_rdlock(&rwl) == 0);
	assert(pthread_rwlock_rdlock(&rwl) == 0);

	/* Create thread. */
	assert(pthread_create(&tid, NULL, thread, (void *)NULL) == 0);

	/* Wait for thread to complete. */
	assert(pthread_join(tid, NULL) == 0);

	/* Release read lock. */
	assert(pthread_rwlock_unlock(&rwl) == 0);
	assert(pthread_rwlock_unlock(&rwl) == 0);
	assert(pthread_rwlock_unlock(&rwl) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
        struct timespec abstime;
        struct timeval now;

	/* Try to acquire a write lock. */
	abstime.tv_sec = 0;
	abstime.tv_nsec = 0;
	assert(pthread_rwlock_timedwrlock(&rwl, &abstime) == ETIMEDOUT);

	assert(gettimeofday(&now, NULL) == 0);
	abstime.tv_sec = now.tv_sec + 2;
	abstime.tv_nsec = 1000 * now.tv_usec;
	assert(pthread_rwlock_timedwrlock(&rwl, &abstime) == ETIMEDOUT);

	pthread_exit(NULL);
}
