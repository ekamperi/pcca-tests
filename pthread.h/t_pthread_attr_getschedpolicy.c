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
#include <limits.h>	/* INT_MAX */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	int policy;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract policy value from attribute object. */
	assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
	assert(policy == SCHED_FIFO || policy == SCHED_RR ||
	       policy == SCHED_OTHER);

	/* Set policy. */
	/* SCHED_FIFO */
	assert(pthread_attr_setschedpolicy(&attr, SCHED_FIFO) == 0);
	policy = -INT_MAX;	/* Paranoia. */
	assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
	assert(policy == SCHED_FIFO);

	/* SCHED_RR */
        assert(pthread_attr_setschedpolicy(&attr, SCHED_RR) == 0);
        policy = -INT_MAX;      /* Paranoia. */
        assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
        assert(policy == SCHED_RR);

	/* SCHED_OTHER */
        assert(pthread_attr_setschedpolicy(&attr, SCHED_OTHER) == 0);
        policy = -INT_MAX;      /* Paranoia. */
        assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
        assert(policy == SCHED_OTHER);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
