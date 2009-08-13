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
#include <ulimit.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	long rv, newlimit;
	int overflowed, unlimited;
	pid_t pid;

	/*
	 * We expect this simple call to succeed.  All return values are
	 * permissible in a successful situation according to the specs.
	 * Which makes me wonder what does exactly a -1 value represent?
	 * Infinite or indefinite (as in inconclusive) limit ? Here we
	 * assume the former.
	 */
	errno = 0;
	rv = ulimit(UL_GETFSIZE);
	assert(rv != -1 || errno == 0);

        /*
	 * Try to increase our file size limit, without being privileged.
	 * Make sure we don't overflow though. Because if we do we may
	 * get false successful outcomes. Also, skip the test if the
	 * previous call to ulimit() returned an infinite limit.
	 */
	unlimited = 0;
	if (rv != -1) {
		overflowed = 0;
		/*
		 * if (rv + 1 > rv) won't overflow on i386/DragonFlyBSD,
		 * but it will on sparc/Solaris 10.
		 */
		newlimit = rv + 1;
		if (newlimit > rv) {
			errno = 0;
			rv = ulimit(UL_SETFSIZE, rv + 1);
			assert(rv == -1 && errno == EPERM);
		} else {
			overflowed = 1;
		}
	} else {
		unlimited = 1;
	}

	/*
	 * Try to lower our file size limit. This doesn't require special
	 * privileges.
	 */
	errno = 0;
	rv = ulimit(UL_SETFSIZE, 0);
	assert(rv != -1 || errno == 0);

	/* Invalid cmd argument. */
	rv = ulimit(-INT_MAX);
	assert(rv == -1 && errno == EINVAL);

	/* The limit must be inherited by a child processes. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		int status;

		/* Wait for child to complete. */
		assert(wait(&status) == pid);

		if (unlimited == 1)
			printf("passed (unlimited)\n");
		else if (overflowed == 1)
			printf("passed (overflowed)\n");
		else
			printf("passed\n");

	} else {
		/* We are inside the child. */
		errno = 0;
		rv = ulimit(UL_GETFSIZE);
		assert(rv == 0);
	}

	return (EXIT_SUCCESS);
}
