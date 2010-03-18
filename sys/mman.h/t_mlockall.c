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

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define CHECK_MLOCK_RETVAL(rv)			\
	assert(rv != -1				\
	    || (rv == -1 && errno == EAGAIN)	\
	    || (rv == -1 && errno == EPERM)	\
	    || (rv == -1 && errno == ENOMEM))

int
main(void)
{
	int rv;

	/*
	 * Lock all of the pages currently mapped into the address space of the
	 * process.
	 */
	rv = mlockall(MCL_CURRENT);
	CHECK_MLOCK_RETVAL(rv);
	rv = munlockall();
	assert(rv != -1 || (rv == -1 && errno == EPERM));

	/*
	 * Lock all of the pages that become mapped into the address space of
	 * the process in the future, when those mappings are established.
	 */
	rv = mlockall(MCL_FUTURE);
	CHECK_MLOCK_RETVAL(rv);
	rv = munlockall();
	assert(rv != -1 || (rv == -1 && errno == EPERM));

	/*
	 * Both.
	 */
	rv = mlockall(MCL_CURRENT | MCL_FUTURE);
	CHECK_MLOCK_RETVAL(rv);
	rv = munlockall();
	assert(rv != -1 || (rv == -1 && errno == EPERM));

	/*
	 * The flags argument is zero.
	 *
	 * Note: EPERM may come before EINVAL in implementations which require
	 * appropriate privileges to lock process memory.
	 */
	rv = mlockall(0);
	assert(rv == -1 && (errno == EPERM || errno == EINVAL));

	printf("passed\n");

	return (EXIT_SUCCESS);
}
