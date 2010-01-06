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
#include <limits.h>	/* INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int
main(void)
{
	/*
	 * getpriority() may return -1 on success, so zero out `errno' in order
	 * to distinguish between a legitimate priority and an error condition.
	 */

	/* Valid nice values are in the range [0, {NZERO}*2-1]. */
	int prio;
	prio = getpriority(PRIO_PROCESS, getpid());
	assert(prio >= 0 && prio <= 2*NZERO - 1);

	/* XXX: ESRCH */

	/* The value of the `which' argument was not recognized. */
	errno = 0;
	assert(getpriority(-112233, 1) == -1 && errno == EINVAL);
	errno = 0;
	assert(getpriority( 112233, 1) == -1 && errno == EINVAL);

	/*
	 * Valid `which' value, but the value of the `who' argument is not a
	 * valid process ID, process group ID, or user ID.
	 */
	errno = 0;
	assert(getpriority(PRIO_PROCESS, -INT_MAX) == -1 && errno == EINVAL);
	errno = 0;
	assert(getpriority(PRIO_PGRP,    -INT_MAX) == -1 && errno == EINVAL);
	errno = 0;
	assert(getpriority(PRIO_USER,    -INT_MAX) == -1 && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
