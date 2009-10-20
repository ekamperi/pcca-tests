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

#define XOPEN_SOURCE 600

#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
	/* Get real and effective group ID. */
	gid_t rgid = getgid();
	gid_t egid = getegid();

	/* This shouldn't change neither real nor effective group ID. */
	assert(setregid(-1, -1) == 0);
	assert(getgid() == rgid);
	assert(getegid() == egid);

	/*
	 * Try to change the real group ID and effective group ID without
	 * being privileged enough. We hope that increasing the old values
	 * by 1, will result in a valid group ID.
	 */
	assert(setregid(rgid + 1, egid + 1) == -1 && errno == EPERM);

	/*
	 * After a failed call to setregid() neither of the group IDs are
	 * changed.
	 */
	assert(getgid() == rgid);
	assert(getegid() == egid);

	/*
	 * Invalid (or so we hope) value of real and effective group ID.
	 *
	 * But since we are not privileged, we may fail with EPERM before the
	 * values reach the validation code! POSIX doesn't say which one takes
	 * precedence over the other.
	 */
	assert(setregid(-INT_MAX, -INT_MAX) == -1 &&
	    (errno == EINVAL || errno == EPERM));

	/*
	 * After a failed call to setregid() neither of the group IDs are
	 * changed.
	 */
	assert(getgid() == rgid);
	assert(getegid() == egid);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
