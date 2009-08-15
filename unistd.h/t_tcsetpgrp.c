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
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t oldpgid, pid;
	int fd, rv, status;

	/* Bad file descriptor. */
	assert(tcsetpgrp(-1, getpgid(0)) == -1 && errno == EBADF);

	/* Invalid process group id. */
	assert(tcsetpgrp(STDOUT_FILENO, -INT_MAX) ==  -1 && errno == EINVAL);

	/* Not a controlling terminal. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(tcsetpgrp(fd, getpgid(0)) == -1 && errno == ENOTTY);
	assert(close(fd) != -1);

	/* Fork! */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		assert(wait(&status) == pid);

		printf("passed\n");
	} else {
		/* We are inside the child. */

		/*
		 * The child process ID doesn't match any active process
		 * group ID. So the following call should fail with EPERM.
		 *
		 * XXX: In Linux this call "succeeds" (i.e. it returns 0),
		 * but the process group id doesn't change at all!
		 */
		assert(tcsetpgrp(STDOUT_FILENO, getpid()) == -1
		    && errno == EPERM);
	}
	
	return (EXIT_SUCCESS);
}
