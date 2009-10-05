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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(void)
{
	pid_t pid;

	/* Fork! */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/*
		 * We are inside the child.
		 *
		 * We are going to call abort() and the SIGABRT signal will be
		 * delivered to us (to the child only).
		 */
		abort();
	} else {
		/*
		 * We are inside the parent.
		 *
		 * We want to explore whether we can determine the exit status
		 * of the aborted child.
		 */

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/* Make sure the child exited due to a signal. */
		assert(WIFSIGNALED(status) != 0);

		/* ... and that the signal was SIGABRT. */
		assert(WTERMSIG(status) == SIGABRT);

		printf("passed\n");

		return (EXIT_SUCCESS);
	}

	/*
	 * Never reached.
	 * (just to silence a gcc warning)
	 */
	return (EXIT_SUCCESS);
}
