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
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define	MQNAME	"/t_mq_send2"

int
main(void)
{
	/* Create a message queue with capacity `1'. */
	struct mq_attr attr;

	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;	/* Maximum message size. */

	/*
	 * We intentionally omit the O_NONBLOCK flag as we want our queue to
	 * operate on blocking mode.
	 */
	mqd_t md;

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0777, &attr);
	assert(md != (mqd_t)-1);

	/* Send a message to fill in the queue. */
	assert(mq_send(md, "foo", sizeof("foo"), /* priority */ 0) != -1);

	/*
	 * Fork and let the child block indefinitely on mq_send().
	 * This would have caused a panic on {Net, DragonFly}BSD, but it is now
	 * fixed.
	 */
	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		mqd_t md2;

		md2 = mq_open(MQNAME, O_WRONLY);
		assert(md2 != (mqd_t)-1);

		assert(mq_send(md2, "foo", sizeof("foo"),
			/* priority */ NULL) != -1);

		/*
		 * There is no point in calling mq_close() here, as (normally)
		 * this code block will never be reached. Instead we do it
		 * inside the parent.
		 */ 
	} else {
		/* We are inside the parent. */
		/* Sleep for a while so that child manages to block on
		 * mq_send().
		 */
		assert(sleep(3) == 0);

		/*
		 * Kill the child. We can't use wait() here, because if let
		 * alone, the child will (normally) live for ever, waiting
		 * on mq_send().
		 */
		assert(kill(pid, SIGKILL) != -1);

		/*
		 * We now probe child's exit status to make sure that everything
		 * went as planned.
		 */
                int status;
                assert(wait(&status) == pid);

		/*
		 * It MUST have exited due to a signal been delivered to it.
		 */
		assert(WIFSIGNALED(status));

		/*
		 * And the signal MUST be the one _we_ send to it (SIGKILL).
		 */
		if (WTERMSIG(status) != SIGKILL) {
			return (EXIT_FAILURE);
		}

		/* Disassociate from message queue. */
		assert(mq_close(md) != -1);

		/* Remove message queue from the system. */
		assert(mq_unlink(MQNAME) != -1);

		printf("passed\n");

		return (EXIT_SUCCESS);
	}

	/* Child will (normally) never reach here. Nor parent. */
	return (EXIT_SUCCESS);
}
