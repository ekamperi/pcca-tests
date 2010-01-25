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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */

#include <sys/types.h>
#include <sys/wait.h>

#define	MQNAME	"/t_mq_parent_child_multmsg"

int
main(void)
{
	/* Parent recites a poem. */
	const char *msg[] = { "But I, being poor, have only my dreams;",
			      "I have spread my dreams under your feet;",
			      "Tread softly because you tread on my",
			      "dreams.",
			      "W.B. Yeats" };

	/* Create the message queue.  */
	mqd_t md;
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != (mqd_t)-1);

	/* Send messages. */
	size_t i, N;

	N = sizeof(msg) / sizeof(msg[0]);
	for (i = 0; i < N; i++) {
		assert(mq_send(md, msg[i], strlen(msg[i]) + 1,
			/* priority */ 0) != -1);
	}

	/* Disassociate with message queue. */
	assert(mq_close(md) != -1);

	/* Fork and have child read the message from parent. */
	pid_t pid;
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		md = mq_open(MQNAME, O_RDONLY | O_NONBLOCK);
		assert(md != (mqd_t)-1);

		char msg_recvd[8192];	/* Implementation defined. */
		for (i = 0; i < N; i++) {
			assert(mq_receive(md, msg_recvd, sizeof(msg_recvd),
				/* priority */ NULL) != -1);

			/*printf("%s\n", msg_recvd);*/
			assert(strcmp(msg_recvd, msg[i]) == 0);
		}

		/* Disassociate with message queue. */
		assert(mq_close(md) != -1);

		/* Remove the message queue from the system. */
		assert(mq_unlink(MQNAME) != -1);
	} else {
		/* We are inside the parent. */

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		printf("passed\n");
	}

	/* Only reached by child. */
	return EXIT_SUCCESS;
}
