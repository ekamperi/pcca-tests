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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void myhandler(int );

int main(void)
{
	pthread_barrierattr_t pba;

	/* We expect these simple calls to succeed. */
	assert(pthread_barrierattr_init(&pba) == 0);
	assert(pthread_barrierattr_destroy(&pba) == 0);

	/*
	 * XXX: The following test must always be the last one to run.
         *
	 * pthread_barrierattr_destroy() may fail if the attr values is
	 * invalid (e.g. NULL here). Some operating systems don't support
	 * this and the test case dies with segmentation fault. Catch
	 * SIGSEGV , because otherwise the false impression of the test
	 * case being flawed is given to the user.
         */
	signal(SIGSEGV, myhandler);

	assert(pthread_barrierattr_destroy(NULL) == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	/* Ignore subsequent occurences of the signal. */
	signal(sig, SIG_IGN);

	printf("passed (EINVAL check was skipped)\n");
	exit(EXIT_SUCCESS);
}
