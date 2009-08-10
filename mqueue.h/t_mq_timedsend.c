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
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <time.h>
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define	MQNAME	"/t_mq_timedsend"

int main(void)
{
	struct mq_attr attr;
	struct timespec abs_timeout;
	mqd_t md, md2;
	pid_t pid;

	/*
	 * Create a message queue for write only with capacity `1'
	 * (we want to emulate a full queue).
	 */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;	/* Maximum message size. */

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != -1);

	/* Send a message to fill the queue. */
	assert(mq_send(md, "foo", sizeof("foo"), /* priority */ 0) != -1);

	/* Timeout in 3 seconds, if the queue doesn't empty. */
	abs_timeout.tv_sec = 3;
	abs_timeout.tv_nsec = 0;

	assert(mq_timedsend(md, "foo", sizeof("foo"), /* priority */ 0,
		&abs_timeout) == -1 && errno == ETIMEDOUT);

	/*
	 * Fork and let parent block on mq_timedsend(). In the meantime,
	 * child receives the existing message from the queue, making room
	 * for parent to send her!
	 */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		md2 = mq_open(MQNAME, O_RDONLY);
		assert(md2 != -2);

		char msg_recvd[8192];	/* Implementation defined. */
		assert(mq_receive(md2, msg_recvd, sizeof(msg_recvd),
			/* priority */ NULL) != -1);

		/* Disassociate from message queue. */
		mq_close(md2);
	} else {
		/* We are inside the parent. */
		/* Make sure the child has completed. */
		int status;
		wait(&status);

		/* This shouldn't block now, since queue isn't full. */
		assert(mq_timedsend(md, "foo", sizeof("foo"), /* priority */ 0,
			&abs_timeout) != -1);

		/* Disassociate from message queue. */
		mq_close(md);

		/* Remove message queue from the system. */
		mq_unlink(MQNAME);

		printf("passed\n");
	}

	return (EXIT_SUCCESS);
}
