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
#include <string.h>

#define	N         100
#define NREADERS   20

struct entry {
	int init;	/* Whether it has been initialized. */
	int code;
} table[N];

pthread_rwlock_t rwl;

/* Function prototypes. */
static void *rdthread(void *);
static void *wrthread(void *);

int main(void)
{
	pthread_t rd[NREADERS], wr;
	int i;

	/* */
	memset(table, 0, N * sizeof(struct entry));

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Create writer thread. */
	assert(pthread_create(&wr, NULL, wrthread, (void *)NULL) == 0);

	/* Create readers threads. */
	for (i = 0; i < NREADERS; i++) {
		assert(pthread_create(&rd[i], NULL, rdthread, (void *)NULL)
		    == 0);
	}

	/* Wait for threads to complete. */
	assert(pthread_join(wr, NULL) == 0);
	for (i = 0; i < NREADERS; i++)
		assert(pthread_join(rd[i], NULL) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
rdthread(void *arg)
{
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < N; j++) {
			assert(pthread_rwlock_rdlock(&rwl) == 0);
			if (table[j].init == 1) {
				assert(table[j].code == j);
			}
			assert(pthread_rwlock_unlock(&rwl) == 0);
		}
	}

	pthread_exit(NULL);
}

static void *
wrthread(void *arg)
{
	int i, j;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < N; j++) {
			assert(pthread_rwlock_wrlock(&rwl) == 0);
			table[j].init = 1;
			table[j].code = j;
			assert(pthread_rwlock_unlock(&rwl) == 0);
		}
	}

	pthread_exit(NULL);
}
