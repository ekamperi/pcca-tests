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
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for sleep() */

#define MQNAME	"/tmqnotifysimple"

int notified = 0;	/* Whether we were notified or not. */

/* Function prototypes. */
static void myhandler(int, siginfo_t *, void *);

int main(void)
{
	mqd_t md;

	/* Create a new message queue. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 0777, NULL);
	assert(md != (mqd_t)-1);

	/*
	 * At this point the message queue is empty.
	 * We then register ourselves for notification, upon the arrival of a
	 * message.
	 */
	struct sigevent sigev;

	sigev.sigev_signo = SIGUSR1;
	sigev.sigev_notify = SIGEV_SIGNAL;
	/* This is a temporary (famous last words) hack for DragonFly. */
#ifndef __DragonFly__
	sigev.sigev_value.sival_int = (int)md;
#endif

	assert(mq_notify(md, &sigev) != -1);

	/* We install a signal handler to catch SIGUSR1. */
	struct sigaction sa;

	sa.sa_sigaction = myhandler;
	sa.sa_flags = SA_SIGINFO;

	assert(sigaction(SIGUSR1, &sa, NULL) != -1);

	/* A little bit paranoid. */
	assert(notified == 0);

	/*
	 * We send one message to the queue so that the transition
	 * empty->non empty takes place and the signal is generated.
	 */
	assert(mq_send(md, "foo", sizeof("foo"), 0) != -1);

	/*
	 * Make sure we were notified, but first sleep a bit so that the
	 * implementation makes it.
	 */
	sleep(1);
	assert(notified == 1);
	notified = 0;

	/* Disassociate with message queue. */
	assert(mq_close(md) != -1);

	/* Remove the message queue from the system. */
	assert(mq_unlink(MQNAME) != -1);

	/* A little bit of paranoia again. We don't want spurious wakeups. */
	assert(notified == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int signo, siginfo_t *info, void *context)
{
	notified = 1;
}
