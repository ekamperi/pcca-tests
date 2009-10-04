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
	mqd_t md2;

	/* Create a message queue for with capacity `1'. */
	struct mq_attr attr;
	mqd_t md;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;	/* Maximum message size. */

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != (mqd_t)-1);

	/* Send a message to fill in the queue. */
	assert(mq_send(md, "foo", sizeof("foo"), /* priority */ 0) != -1);

	/*
	 * Fork and let the parent block on mq_timedsend().
	 * Meanwhile, the child receives the old message from the queue, making
	 * room for parent to send the new one!
	 */
	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		md2 = mq_open(MQNAME, O_RDONLY);
		assert(md2 != (mqd_t)-1);

		char msg_recvd[8192];	/* Implementation defined. */
		assert(mq_receive(md2, msg_recvd, sizeof(msg_recvd),
			/* priority */ NULL) != -1);

		/* Disassociate from message queue. */
		mq_close(md2);
	} else {
		/* We are inside the parent. */
		/* Make sure the child has completed. */
		int status;
		assert(wait(&status) == pid);

		/*
		 * This shouldn't timeout now, since the queue is or is about to
		 * become empty. It may block though for a while.
		 */
		struct timespec now, timeout;

		assert(clock_gettime(CLOCK_REALTIME, &now) == 0);
		timeout.tv_sec  = now.tv_sec + 3;
		timeout.tv_nsec = now.tv_nsec;

		assert(mq_timedsend(md, "foo", sizeof("foo"), /* priority */ 0,
			&timeout) != -1);

		/* Disassociate from message queue. */
		mq_close(md);

		/* Remove message queue from the system. */
		mq_unlink(MQNAME);

		printf("passed\n");
	}

	return (EXIT_SUCCESS);
}
