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
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* How many signals were raised */
volatile sig_atomic_t cnt = 0;

static void
myhandler(int sig) {
	if (sig == SIGUSR1) {
		++cnt;
	} else {
		/* Severely penalize spurious signals */
		cnt -= 1000;
	}
}

int
main(void)
{
	/*
	 * SIGSTKSZ is the default size in bytes for the alternate signal stack
	 */
	stack_t s;

	s.ss_sp = malloc(SIGSTKSZ);
	assert(s.ss_sp != NULL);
	s.ss_size = SIGSTKSZ;
	s.ss_flags = 0;

	/*
	 * Install alternate stack for signal handlers for the current thread
	 */
	assert(sigaltstack(&s, NULL) != -1);

	/*
	 * Install custom signal handler for SIGSEGV
	 *
	 * SA_ONSTACK causes signal delivery to occur on an alternate stack
	 */
	struct sigaction sa;

	sa.sa_handler = myhandler;
	sa.sa_flags = SA_ONSTACK;
	assert(sigemptyset(&sa.sa_mask) != -1);

	assert(sigaction(SIGUSR1 , &sa, NULL) != -1);

	/* Generate a bunch of signals */
#define NSIGNALS	1000
	size_t i;

	for (i = 0; i < NSIGNALS; i++) {
		assert(kill(getpid(), SIGUSR1) != -1);
	}

	/* Sleep a bit, just to be sure that the last signal made it through */
	sleep(1);

	/* Make sure nothing was lost in translation */
	assert(cnt == NSIGNALS);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
