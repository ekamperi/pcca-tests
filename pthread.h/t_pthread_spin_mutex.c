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

int main(void)
{
	pthread_spinlock_t lock;
	pthread_mutex_t mtx;

	/* Initialize spinlock. */
	assert(pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Acquire spinlock. */
	assert(pthread_spin_lock(&lock) == 0);

	/* Initialize mutex. */
	assert(pthread_mutex_init(&mtx, NULL) == 0);

	/* Acquire mutex. */
	assert(pthread_mutex_lock(&mtx) == 0);

	/* Release mutex. */
	assert(pthread_mutex_unlock(&mtx) == 0);

	/* Destroy mutex. */
	assert(pthread_mutex_destroy(&mtx) == 0);

	/* Release spinlock. */
	assert(pthread_spin_unlock(&lock) == 0);

	/* Destroy spinlock. */
	assert(pthread_spin_destroy(&lock) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
