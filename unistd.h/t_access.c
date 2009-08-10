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
#include <unistd.h>

int main(void)
{
	/* We expect the following calls to succeed. */
	assert(access("sandbox/file777", F_OK) != -1);
	assert(access("sandbox/file777", R_OK) != -1);
	assert(access("sandbox/file777", W_OK) != -1);
	assert(access("sandbox/file777", X_OK) != -1);

	assert(access("sandbox/file666", F_OK) != -1);
	assert(access("sandbox/file666", R_OK) != -1);
	assert(access("sandbox/file666", W_OK) != -1);

	assert(access("sandbox/file555", F_OK) != -1);
	assert(access("sandbox/file555", R_OK) != -1);
	assert(access("sandbox/file555", X_OK) != -1);

	assert(access("sandbox/file000", F_OK) != -1);

	/* ... and these to fail. */
	assert(access("sandbox/file666", X_OK) == -1 && errno == EACCES);

	assert(access("sandbox/file555", W_OK) == -1 && errno == EACCES);

	assert(access("sandbox/file000", R_OK) == -1 && errno == EACCES);
	assert(access("sandbox/file000", W_OK) == -1 && errno == EACCES);
	assert(access("sandbox/file000", X_OK) == -1 && errno == EACCES);


	/*
	 * A loop exists in symbolic links encountered during resolution of the
	 * path argument.
	 */
	assert(access("sandbox/infloop", F_OK) == -1 && errno == ELOOP);

	/* XXX: ENAMETOOLONG */

	/* Probe non existent paths or empty string. */
	assert(access("", F_OK) == -1 && errno == ENOENT);
	assert(access("/sandbox/thisshouldntexist", F_OK) == -1 &&
	    errno == ENOENT);

        /* This is optional. */
	int rv = 0;

        rv = access("sandbox/file777", ~(R_OK | W_OK | X_OK | F_OK));
	if (rv == -1) {
		/* If it failed, we demand it to be EINVAL. */
		assert(errno == EINVAL);
	}

	if (rv == -1)
		printf("passed\n");
	else
		printf("passed (EINVAL check skipped)\n");

	return (EXIT_SUCCESS);
}
