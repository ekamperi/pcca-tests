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
#include <string.h>	/* for memset() */
#include <unistd.h>

int
main(void)
{
	char *buf;
	long sz = 32768;	/* Default value for PATH_MAX */

#ifdef _PC_PATH_MAX
	/* Determine maximum path length. */
	sz = pathconf(".", _PC_PATH_MAX);
	assert(sz != -1);	/* We surely don't allow infinite size
				   path names. */
#endif
	buf = malloc(sz);
	assert(buf != NULL);
	memset(buf, 0xff, sz);	/* Make sure we don't terminate prematurely. */

	assert(chdir(buf) == -1 && errno == ENAMETOOLONG);

	free(buf);

	/* Search permission is denied for any component of the pathname. */
	assert(chdir("sandbox/dir666/whatever") == -1 && errno == EACCES);

	/*
	 * A loop exists in symbolic links encountered during resolution of the
	 * path argument.
	 */
	assert(chdir("sandbox/infloop") == -1 && errno == ELOOP);

	/* Path doesn't name an existing directory or is an empty string. */
	assert(chdir("/sandbox/thisdefinitelydoesntexist") == -1
	       && errno == ENOENT);
	assert(chdir("") == -1 && errno == ENOENT);

	/* A path's component is not a directory. */
	assert(chdir("sandbox/notadir") == -1 && errno == ENOTDIR);

	/* We expect this simple call to succeed. */
	assert(chdir(".") == 0);

	/* XXX: This must be the last condition to be checked. */
	assert(chdir("..") == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
