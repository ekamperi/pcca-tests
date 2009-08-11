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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for pid_t */
#include <sys/resource.h>

int main(void)
{
	pid_t pid;
	int prio;

	/* We expect this simple operation to succeed. */
	pid = getpid();

	assert(setpriority(PRIO_PROCESS, pid, 2) == 0);

	/* getpriority() can return -1 on success, so zero out errno. */
	errno = 0;
	prio = getpriority(PRIO_PROCESS, pid);
	assert(prio != -1 || errno == 0);
	assert(prio == 2);

	/* Invalid `which' value. */
	assert(setpriority(-112233, 1, /* nice */ 0) == -1 && errno == EINVAL);
	assert(setpriority( 112233, 1, /* nice */ 0) == -1 && errno == EINVAL);

	/* Valid `which' value, but no process with `which,who' pair found. */
	assert(setpriority(PRIO_USER, -1, /* nice */ 0) == -1
	    && errno == ESRCH);

        /* Try to mess around with the mother of all process. */
        assert(setpriority(PRIO_PROCESS, 1, /* nice */ 0) == -1
	    && errno == EPERM);

#if 0
	/*
	 * Be bad and try to lower our nice value, without having privilege.
	 * POSIX only suggests in this matter, so we can't expect one behaviour.
	 * E.g, the OS may renice up to the minimum allowed nice value
	 * (DragonFly does).
	 */
	pid_t pid;
	pid = getpid();

	assert(setpriority(PRIO_PROCESS, pid, /* nice */ -10) == -1
	    && errno == EACCES);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
