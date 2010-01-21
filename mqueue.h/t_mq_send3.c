/*
 * Copyright (c) 2010, Stathis Kamperis
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
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MQNAME    "/t_mq_send3"
#define NMESSAGES 10

int
main(void)
{
	/* Create message queue with maxmsg `10'. */
	struct mq_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = NMESSAGES;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;		/* Maximum message size. */

	/*
	 * We intentionally omit the O_NONBLOCK flag as we want our queue to
	 * operate on blocking mode.
	 */
	mqd_t md;

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 700, &attr);
	assert(md != (mqd_t)-1);

	/*
	 * A little bit of paranoia.
	 * Make sure that the maximum number of messages is equal to what we
	 * set it. I.e., it didn't round up under our feet, which would defeat
	 * the whole purpose of the test.
	 */
	memset(&attr, 0, sizeof(attr));

	assert(mq_getattr(md, &attr) != -1);
	assert(attr.mq_maxmsg == NMESSAGES);

	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */

		/*
		 * Send one more message than the maximum messages the queue
		 * can hold. In the last message, the mq_send() call will block.
		 */
		size_t i;

		for (i = 0; i < NMESSAGES + 1; i++) {
			assert(mq_send(md, "foo", sizeof("foo"),
				/* priority */ i + 1) != -1);
		}
	} else {
		/*
		 * We are inside the parent.
		 *
		 * Sleep a bit so that child takes its time to block on
		 * mq_send().
		 */
		assert(sleep(2) == 0);

		/*
		 * Start draining messages from the queue.
		 * Messages are sent with increasing priority, so the last sent
		 * is the first to be delivered.
		 */
		char buf[1024];
		unsigned int prio;

		/*
		 * 10th message --
		 * this means that the last mq_send() call blocked.
		 */
		assert(mq_receive(md, buf, sizeof(buf), &prio) != -1);
		assert(prio == NMESSAGES);

		assert(sleep(1) == 0);

		/*
		 * 11th message --
		 * this means that the last mq_send() call unblocked as it ought
		 * to.
		 */
		assert(mq_receive(md, buf, sizeof(buf), &prio) != -1);
		assert(prio == NMESSAGES + 1);

		/* We are done -- cleanup */
		assert(mq_close(md) != -1);
		assert(mq_unlink(MQNAME) != -1);

		printf("passed\n");

		return (EXIT_SUCCESS);
	}

	/* Only reached by the child. */
	return (EXIT_SUCCESS);
}
