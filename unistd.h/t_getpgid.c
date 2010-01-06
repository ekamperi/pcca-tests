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

	/* Get process group ID of the current process (both ways). */
	assert(getpgid(0) == getpgid(getpid()));

	/* EINVAL is optional, but we must allow it as it may precede ESRCH. */
	assert(getpgid(-INT_MAX) == (pid_t)-1
	    && (errno == ESRCH || errno == EINVAL));

	/* Fork and let child create a new session. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */

		/* Allow the child to create a new session. */
		sleep(1);

		/*
		 * Try to retrieve the process group ID from child which now
		 * belongs to another session. This may optionally fail with
		 * EPERM.
		 * By the time I write this, only OpenBSD "succeeds to fail".
		 * {Free, Net, DragonFly}BSD, Linux and Solaris 10 all let you
		 * get away with it. Which, I repeat, is ok by POSIX.
		 *
		 * openbsd/sys/kern/kern_prot.c#101
		 */
		int passed;

		if (getpgid(pid) != (pid_t)-1) {
			passed = 1;
		} else {
			assert(errno == EPERM);
			passed = 2;
		}

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/*
		 * Determine if the child exited normally, or due to a SIGABRT
		 * signal being delivered to it by a failed assertion.
		 */
		if (WIFSIGNALED(status)) {
			assert(WTERMSIG(status) == SIGABRT);
			return (EXIT_FAILURE);
		}

		if (passed == 1)
			printf("passed (EPERM check skipped)\n");
		else
			printf("passed\n");

		return (EXIT_SUCCESS);
	} else {
		/* We are inside the child. */

		/* Create a new session. */
		assert(setsid() != (pid_t)-1);

		/* And then sleep for a while, so that parent can probe us. */
		sleep(2);
	}

	/* Only reached by child upon success. */
	return (EXIT_SUCCESS);
}
