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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t signal1 = 0;
volatile sig_atomic_t signal2 = 0;

static void
myhandler1(int sig)
{
	if (sig == SIGUSR1) {
		++signal1;
	} else {
		/* Severely penalize spurious signals */
		signal1 -= 1000;
	}
}

static void
myhandler2(int sig)
{
	if (sig == SIGUSR2) {
		++signal2;
	} else {
		/* Severely penalize spurious signals */
		signal1 -= 1000;
	}
}

int
main(void)
{
	/*
	 * When SIGUSR1 or SIGUSR2 is raised, we want are custom handlers to be
	 * invoked.
	 */
	struct sigaction sa1, sa2;

	sa1.sa_handler = myhandler1;
	sa2.sa_handler = myhandler2;
	sa1.sa_flags = 0;
	sa2.sa_flags = 0;

	assert(sigemptyset(&sa1.sa_mask) != -1);
	assert(sigemptyset(&sa2.sa_mask) != -1);

	assert(sigaction(SIGUSR1, &sa1, 0) != -1);
	assert(sigaction(SIGUSR2, &sa2, 0) != -1);

	/*
	 * When the timers expire, we want to be notified via signal
	 * generation.
	 */
	struct sigevent se1, se2;

	se1.sigev_notify = SIGEV_SIGNAL;
	se2.sigev_notify = SIGEV_SIGNAL;
	se1.sigev_signo = SIGUSR1;
	se2.sigev_signo = SIGUSR2;

	/* Create the timers */
	timer_t tid1, tid2;

	assert(timer_create(CLOCK_REALTIME, &se1, &tid1) != -1);
	assert(timer_create(CLOCK_REALTIME, &se2, &tid2) != -1);

	/*
	 * If the flag TIMER_ABSTIME is not set in the argument flags,
	 * timer_settime() shall behave as if the time until next expiration is
	 * set to be equal to the interval specified by the it_value member of
	 * value.
	 */
	int flags = 0;
	struct itimerspec its;

	flags &= ~TIMER_ABSTIME;

	its.it_value.tv_sec = 1;
	its.it_value.tv_nsec = 0;

	assert(timer_settime(tid1, flags, &its, NULL) != -1);
	assert(timer_settime(tid2, flags, &its, NULL) != -1);

	/*
	 * Ensure that sleep() is interrupted by the signal delivery.
	 * This means that our signals have been generated in time.
	 */
	assert(sleep(3) < 3);

	/* We want both signals to be raised */
	assert(signal1 == 1 && signal2 == 1);

	/*
	 * Timers that have expired need not to be explicitly destroyed with
	 * timer_delete().
	 */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
