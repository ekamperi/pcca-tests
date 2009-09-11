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
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd;

	/* Invalid file descriptor. */
	assert(lockf(-1, F_TLOCK, 0) == -1 && errno == EBADF);

	/*
	 * Valid file descriptor, but F_LOCK or F_TLOCK is supplied,
	 * and fd is not open for writing.
	 */
	fd = open("sandbox/file777", O_RDONLY);
	assert(fd != -1);

	assert(lockf(fd, F_LOCK, 0) == -1 && errno == EBADF);
	assert(lockf(fd, F_TLOCK, 0) == -1 && errno == EBADF);

	assert(close(fd) != -1);

	/* Invalid `function' requested. */
	fd = open("sandbox/file777", O_RDWR);
	assert(fd != -1);
	assert(lockf(fd, -INT_MAX, 0) == -1 && errno == EINVAL);

	/* Size plus current file offset is less than 0. */
	assert(lseek(fd, 0, SEEK_SET) != -1);	/* Just a sanity check. */
	assert(lockf(fd, F_TLOCK, -1) == -1 && errno == EINVAL);

	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
