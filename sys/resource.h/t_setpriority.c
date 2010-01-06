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
#include <limits.h>	/* INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for pid_t */
#include <sys/resource.h>

int
main(void)
{
	pid_t pid;
	int prio, prio2;

	/* Make sure we don't run the test as root. */
	if (getuid() == 0) {
		fprintf(stderr, "FATAL: Test cases shouldn't be running "
		    "as root user!\n");
		assert(getuid() != 0);
	}

	pid = getpid();

	/*
	 * getpriority() may return -1 on success, so zero out `errno' in order
	 * to distinguish between a legitimate priority and an error condition.
	 */
	errno = 0;
	prio = getpriority(PRIO_PROCESS, pid);
	assert(prio != -1 || errno == 0);

	/*
	 * Increasing our nice values shouldn't require escalated privileges.
	 * The implementation shall enforce the highest supported value, if by
	 * any chance `prio + 1' is out of range.
	 */
	assert(setpriority(PRIO_PROCESS, pid, prio + 1) == 0);
	prio2 = getpriority(PRIO_PROCESS, pid);
	assert(prio2 == prio || prio2 == prio + 1);

	/* XXX: ESRCH */

	/* The value of the `which' argument was not recognized. */
	errno = 0;
	assert(setpriority(-112233, pid, /* nice */ 0) == -1
	    && errno == EINVAL);
	errno = 0;
	assert(setpriority( 112233, pid, /* nice */ 0) == -1
	    && errno == EINVAL);

	/*
	 * Valid `which' value, but the value of the `who' argument is not a
	 * valid process ID, process group ID, or user ID.
	 */
	errno = 0;
	assert(setpriority(PRIO_PROCESS, -INT_MAX, /* nice */ 0) == -1
	       && errno == EINVAL);
	errno = 0;
	assert(setpriority(PRIO_PGRP,    -INT_MAX, /* nice */ 0) == -1
	       && errno == EINVAL);
	errno = 0;
	assert(setpriority(PRIO_USER,    -INT_MAX, /* nice */ 0) == -1
	       && errno == EINVAL);

        /* Try to mess around with init, the mother of all processes. */
	errno = 0;
        assert(setpriority(PRIO_PROCESS, /* init */ 1, 0) == -1
	       && errno == EPERM);

	/*
	 * Be naughty and try to lower our nice value, without having enough
	 * privileges.
	 */
	errno = 0;
	assert(setpriority(PRIO_PROCESS, pid, /* nice */ -INT_MAX) == -1
	    && errno == EACCES);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
