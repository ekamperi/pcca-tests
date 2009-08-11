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

int cancelled1 = 1;
int cancelled2 = 1;

/* Function prototypes. */
static void *thread1(void *);
static void *thread2(void *);

int main(void)
{
	pthread_t th1, th2;

	/* Create the threads. */
	assert(pthread_create(&th1, NULL, thread1, (void *)NULL) == 0);
	assert(pthread_create(&th2, NULL, thread2, (void *)NULL) == 0);

	/* Request from threads to cancel. */
	assert(pthread_cancel(th1) == 0);
	assert(pthread_cancel(th2) == 0);

	/* Wait for threads to complete. */
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	/* Make sure ony the first was cancelled. */
	assert(cancelled1 && !cancelled2);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread1(void *arg)
{
	/*
	 * Sleep for 1 second to give main thread the time to call
	 * pthread_cancel() on us.
	 */
	sleep(1);

	/*
	 * Create a cancellation point, right here, right now.
	 * By default new threads have cancelability enabled,
	 * so there is no need to explicitly set it.
	 */
	pthread_testcancel();

	/* If we have reached here, we failed. */
	cancelled1 = 0;

	pthread_exit(NULL);
}

static void *
thread2(void *arg)
{
	int oldstate;

	/* Same as before, but now we disable cancelability. */
	assert(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate) == 0);

        /*
         * Sleep for 1 second to give main thread the time to call
	 * pthread_cancel() on us.
         */
	sleep(1);

	pthread_testcancel();

	/* If we have reached here, we succeeded. */
	cancelled2 = 0;

	pthread_exit(NULL);
}
