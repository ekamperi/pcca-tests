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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	/* Get the session leader of us. */
	assert(getsid((pid_t)0) != (pid_t)-1);

	/* There is (hopefully) no process with this process ID. */
	assert(getsid((pid_t)-INT_MAX) == (pid_t)-1 && errno == ESRCH);

	/* Fork and let child create a new session. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */

		/* Allow the child to create a new session. */
		sleep(1);

		/*
		 * Probe child to report it session leader.
		 *
		 * Let me quote Issue 6 on this one. "The getsid() function
		 * shall fail with EPERM if the process specified by pid is not
		 * in the same session as the calling process, and the imple-
		 * mentation does not allow access to the process group ID of
		 * the session leader of that process from the calling process."
		 *
		 * If my interpretation is right, POSIX doesn't mandate for an
		 * implementation to deny this type of access. But IF it does,
		 * then it _should_ fail with EPERM.
		 */
		if (getsid(pid) == (pid_t)-1) {
			assert(errno == EPERM);
			printf("passed\n");
		}
		else
			printf("passed (EPERM check skipped)\n");

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);
	} else {
		/* We are inside the child. */

		/* Create a new session. */
		assert(setsid() != (pid_t)-1);

		/* And then sleep for a while, so that parent can probe us. */
		sleep(2);
	}

	return (EXIT_SUCCESS);
}
