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
#include <unistd.h>

int isdeadlock = 1;

/* Function prototypes. */
static void *deadthread(void *);

int main(void)
{
	pthread_t deadtid;

	/* Create thread. */
	assert(pthread_create(&deadtid, NULL, deadthread, (void *)NULL) == 0);

	/*
	 * We can't call pthread_join(), because we don't know whether the
	 * implementation supports deadlock detection. Instead, we sleep for
	 * 1 second.
	 */
	assert(sleep(1) == 0);

	assert(!isdeadlock);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
deadthread(void *arg)
{
        pthread_rwlock_t rwl;

        /* Create read-write lock with default parameters. */
        assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire a read lock, followed by a write lock. */
        assert(pthread_rwlock_rdlock(&rwl) == 0);
        assert(pthread_rwlock_wrlock(&rwl) == EDEADLK);

	/* Release read lock. */
	assert(pthread_rwlock_unlock(&rwl) == 0);

        /* Destroy read-write lock. */
        assert(pthread_rwlock_destroy(&rwl) == 0);

	isdeadlock = 0;

	pthread_exit(NULL);
}
