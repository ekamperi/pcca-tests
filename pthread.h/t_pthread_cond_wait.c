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

int main(void)
{
	pthread_cond_t cond;
	pthread_mutex_t mtx;
	struct timespec abstime;

	/* Create a condition variable with default attributes. */
	assert(pthread_cond_init(&cond, NULL) == 0);

	/* Initialize mutex. */
	assert(pthread_mutex_init(&mtx, NULL) == 0);

	/* Acquire lock. */
	assert(pthread_mutex_lock(&mtx) == 0);

	/* Invalid absolute time. */
	abstime.tv_sec = -1;
	abstime.tv_nsec = 0;
	assert(pthread_cond_timedwait(&cond, &mtx, &abstime) == EINVAL);

	abstime.tv_sec = 0;
        abstime.tv_nsec = -1;
        assert(pthread_cond_timedwait(&cond, &mtx, &abstime) == EINVAL);

        assert(pthread_cond_timedwait(&cond, &mtx, NULL) == EINVAL);

	/* Timeout has passed. */
	abstime.tv_sec = 0;
	abstime.tv_nsec = 0;
	assert(pthread_cond_timedwait(&cond, &mtx, &abstime) == ETIMEDOUT);

	/* Release lock. */
	assert(pthread_mutex_unlock(&mtx) == 0);

	/* Cleanup. */
	assert(pthread_cond_destroy(&cond) == 0);
	assert(pthread_mutex_destroy(&mtx) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
