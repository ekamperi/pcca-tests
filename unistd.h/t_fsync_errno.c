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
#include <errno.h>
#include <limits.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
	/*
	 * 3.165 File Descriptor
	 * The value of a file descriptor is from zero to {OPEN_MAX}.
	 */
	assert(fsync(-1) == -1 && errno == EBADF);
	assert(fsync(-2) == -1 && errno == EBADF);
	assert(fsync(-INT_MAX) == -1 && errno == EBADF);

	/* Try to fsync() an unfsyncable object, such as a pipe */
	int fd[2];

	assert(pipe(fd) != -1);
	assert(fsync(fd[0]) == -1 && errno == EINVAL);
	assert(fsync(fd[1]) == -1 && errno == EINVAL);

	assert(close(fd[0]) != -1);
	assert(close(fd[1]) != -1);

	/* Same as before, but use a message queue descriptor */
#define MQNAME	"/t_fsync_errno_mq"
	mqd_t md;
	md = mq_open(MQNAME, O_RDWR | O_CREAT, 777, NULL);
	assert(md != (mqd_t)-1);

	assert(fsync(md) == -1 && errno == EINVAL);

	assert(mq_close(md) != -1);
	assert(mq_unlink(MQNAME) != -1);

	printf ("passed\n");

	return (EXIT_SUCCESS);
}
