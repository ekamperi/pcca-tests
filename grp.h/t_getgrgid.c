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
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	struct group *gr, *res;
	gid_t gid;

	/* Get the real group ID of the calling process. */
	gid = getgid();

	/* Search the group database for an entry with a matching `gid'. */
	gr = getgrgid(gid);
	assert(gr != NULL);

	/*
	 * Test the thread safe version of it.
	 * XXX: Perhaps better use many threads ?
	 **/

	/*
	 * We need to determine the maximum size of the buffer needed by
	 * getgrgid_r(). If we can't query its value via sysconf(), we make
	 * a guess and use some adequately large for the common case, value.
	 */
	long rv = 65536;
#ifdef _SC_GETGR_R_SIZE_MAX
	rv = sysconf(_SC_GETGR_R_SIZE_MAX);
	assert(rv != -1);	/* We don't allow for indefinite values,
				   rv == -1 && errno == unchanged. */
#endif
	char *buf = malloc(rv);
	assert(buf != NULL);

	assert(getgrgid_r(gid, gr, buf, rv, &res) == 0);

	/*
	 * Just a sanity check; res shouldn't be NULL if the call was
	 * successful and we had a match.
	 */
	assert(res != NULL);

	/* Iterate over all members of our group. */
	while(*gr->gr_mem) {
		/*printf("-> %s\n", *gr->gr_mem);*/
		gr->gr_mem++;
	}

	/* Free buffer. */
	free(buf);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
