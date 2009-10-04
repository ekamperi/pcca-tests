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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <time.h>
#include <sys/time.h>

#define MQNAME	"/t_mq_timedsend"

int main(void)
{
	/*
	 * We need a full message queue for mq_timedsend() to block on it and
	 * time out. For this purpose, we start with a queue of capacity equal
	 * to one `1', that can be easily filled in.
	 */
	struct mq_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;     /* Maximum number of messages. */
	attr.mq_msgsize = 1024; /* Maximum message size. */

	/* Create the queue. */
	mqd_t md;

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != (mqd_t)-1);

	/*
	 * Send a message to exhaust the capacity of the queue. Since noone is
	 * receiveing the message, the queue will remain filled, which is what
	 * we want.
	 */
	assert(mq_send(md, "foo", sizeof("foo"), /* priority */ 0) != -1);

	/* Timeout in 3 seconds, if the queue doesn't become empty (it wont). */
	struct timespec now, timeout;

	assert(clock_gettime(CLOCK_REALTIME, &now) == 0);
	timeout.tv_sec  = now.tv_sec + 3;
	timeout.tv_nsec = now.tv_nsec;

	/*
	 * Since we don't trust mq_timedsend(), we are going to manually measure
	 * the time ellapsed until the function call times out.
	 */
	struct timeval tv1, tv2;

	assert(gettimeofday(&tv1, NULL) == 0);

	/* This should timeout in ~3 seconds. */
	assert(mq_timedsend(md, "foo", sizeof("foo"), /* priority */ 0,
		&timeout) == -1 && errno == ETIMEDOUT);

	/* Mark the end. */
	assert(gettimeofday(&tv2, NULL) == 0);

	/* Make sure the time ellapsed is roughly 3sec. */
	long int msec;

	msec = (tv2.tv_sec - tv1.tv_sec) * 1000 +
	       (tv2.tv_usec - tv1.tv_usec) / 1000;
	assert(msec >= 2900 && msec <= 3100);

	/* Cleanup. */
	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
