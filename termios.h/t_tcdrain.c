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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/wait.h>

int issignaled = 0;

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	pid_t pgid, pid;
	int fd;

        /* Make sure we are associated with a tty. */
	assert(isatty(STDOUT_FILENO) != 0);

	/* Bad file descriptor. */
	assert(tcgetsid(-1) == (pid_t)-1 && errno == EBADF);

	/* File descriptor is not associated with a terminal. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(tcgetsid(fd) == (pid_t)-1 && errno == ENOTTY);
	assert(close(fd) != -1);

	/* Fork! */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		/* Make us the foreground process group. */
		pgid = getpgid(0);
		assert(tcsetpgrp(STDOUT_FILENO, pgid) == 0);

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

		printf("passed\n");

		return (EXIT_SUCCESS);
	} else {
		/* We are inside the child. */
		/*
		 * Wait for parent to become foreground process group.
		 * XXX: Is it really needed ?
		 */
		sleep(1);

		/* Install signal handler. */
		signal(SIGTTOU, myhandler);

		/*
		 * Create a new process group. And since the old one is the
		 * foreground, that leaves us with being the background process
		 * group.
		 */
		pid = getpid();
		assert(setpgid(0, pid) == 0);

		/*
		 * This should raise SIGTTOU signal to us, because we try to
		 * write to the terminal while belonging to a background process
		 * group.
		 */
		assert(tcdrain(STDOUT_FILENO) == 0);

		assert(issignaled == 1);
	}

        /* Only reached by child upon success. */
	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	signal(SIGTTOU, SIG_IGN);
	issignaled = 1;
}
