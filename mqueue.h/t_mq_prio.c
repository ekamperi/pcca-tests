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
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define	MQNAME	"/t_mq_prio"

mqd_t md;

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	const char lowmsg[] = "Parent says hello";
	const char highmsg[] = "Parent asks for HELP";
	unsigned int prio;
	int rv;
	pid_t pid;

	signal(SIGABRT, myhandler);

	/* Create a message queue for write only with default parameters. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert (md != -1);

	/* Send messages, low first, then high. */
	rv = mq_send(md, lowmsg, sizeof(lowmsg), /* priority */ 0);
	assert(rv != -1);

	rv = mq_send(md, highmsg, sizeof(highmsg), /* priority */ 1);
	assert(rv != -1);

	/* Disassociate with message queue. */
	rv = mq_close(md);
	assert(rv != -1);

	/* Fork and have child read the message from parent. */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		md = mq_open(MQNAME, O_RDONLY);
		assert(md != -1);

		char msg_recvd[8192];	/* Implementation defined. */
		rv = mq_receive(md, msg_recvd, sizeof(msg_recvd), &prio);
		assert(rv != -1);
		/*
		 * Make sure that the message with higher priority,
		 * is delivered first of all.
		 */
		assert(strcmp(msg_recvd, highmsg) == 0 && prio == 1);

		rv = mq_receive(md, msg_recvd, sizeof(msg_recvd), &prio);
		assert(rv != -1);
		assert(strcmp(msg_recvd, lowmsg) == 0 && prio == 0);

		/* Disassociate with message queue. */
		rv = mq_close(md);
		assert(rv != -1);

		/* Remove the message queue from the system. */
		rv = mq_unlink(MQNAME);
		assert(rv != -1);

		printf("passed\n");
	} else {
		/* We are inside the parent. */
		int status;
		assert(wait(&status) == pid);
	}

	return EXIT_SUCCESS;
}

static void
myhandler(int sig)
{
	/*
	 * Message queues' name & resources are persistent, i.e., they live
	 * even after the process dies. That's why, disassociate and destroy
	 * the queue on failure, or else we might end up with zombie queues and
	 * hit the limit of max open queues.
	 * Also, we don't care about the return value of the following calls.
	 */
	mq_close(md);
	mq_unlink(MQNAME);

	/* After this, the program will abort. */
}
