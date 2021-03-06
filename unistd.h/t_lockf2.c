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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int fd;

	/* Open file. */
	fd = open("sandbox/file777", O_RDWR);
	assert(fd != -1);

	/* Fork. */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		/* Acquire the lock. */
		assert(lockf(fd, F_LOCK, 0) != -1);

		/*
		 * We need to sleep here. If we don't, the child will terminate,
		 * and the locks held by it released, which will bring us to
		 * square one.
		 */
		assert(sleep(2) == 0);
	} else {
		/* We are inside the parent. */
		/* Sleep a bit, so that the child can acquire the lock. */
		assert(sleep(1) == 0);

		/*
		 * Just a sanity check.
		 * Make sure the child has actually acquired the lock.
		 */
		assert(lockf(fd, F_TEST, 0) == -1);
		assert(errno == EACCES || errno == EAGAIN);

		/*
		 * Try to re-acquire the lock.
		 * As parent, we are a different process now and we should fail.
		 */
		assert(lockf(fd, F_TLOCK, 0) == -1);
		assert(errno == EACCES || errno == EAGAIN);

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		assert(close(fd) != -1);

		printf("passed\n");
	}

	return (EXIT_SUCCESS);
}
