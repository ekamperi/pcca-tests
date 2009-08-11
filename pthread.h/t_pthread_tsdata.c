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
#include <stdlib.h>
#include <stdio.h>

pthread_key_t	tsdkey;		/* Thread specific data key. */
struct tsdata {			/* Thread specific data. */
	int x;
	int y;
};

/* Function prototypes. */
static void *thread(void *);
static void helper(void);
static void destructor(void *);

int main(void)
{
#define NTHREADS 10
	pthread_t thpool[NTHREADS];
	struct tsdata *ptsdata;
	size_t i;

	/*
	 * Create a thread specific data key, that we will use to locate our
	 * thread specific data. The key will be visible to all threads in the
	 * process.
	 */
	assert(pthread_key_create(&tsdkey, destructor) == 0);

	/* Create threads. */
	for (i = 0; i < NTHREADS; i++) {
		ptsdata = malloc(sizeof(struct tsdata));
		assert(ptsdata != NULL);

		ptsdata->x = i;
		ptsdata->y = 2*i;

		assert(pthread_create(&thpool[i], NULL, thread, (void *)ptsdata)
		    == 0);
	}

	/* Wait for threads to complete. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Destroy key. */
	pthread_key_delete(tsdkey);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	struct tsdata *ptsdata;
	
	/* Retrieve data. */
	ptsdata = (struct tsdata *)arg;

	/*
	 * Associate the thread specific data with a key.
	 * Different threads may bind different values to the same key.
	 */
	assert(pthread_setspecific(tsdkey, ptsdata) == 0);

	/* Make a call to a helper function. */
	helper();

	pthread_exit(NULL);
}

static void
helper(void)
{
	struct tsdata *ptsdata;

	/* Get the thread specific data associated with the key. */
	ptsdata = pthread_getspecific(tsdkey);
	assert(ptsdata != NULL);

	assert(ptsdata->y == 2*ptsdata->x);
}

static void
destructor(void *arg)
{
	free(arg);
}
