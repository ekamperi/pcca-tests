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

#define PATH_MAX 1024

int
main(void)
{
	char actualpath[PATH_MAX + 1];
#if 0
	/* Read or search permission was denied for a component of filename. */
	assert(realpath("sandbox/file000", actualpath) == NULL
	    && errno == EACCES);
#endif

	/* The filename argument is a null pointer. */
	assert(realpath(NULL, actualpath) == NULL && errno == EINVAL);

	/*
	 * A loop exists in symbolic links encountered during resolution of the
	 * filename argument.
	 */
	assert(realpath("sandbox/infloop", actualpath) == NULL
	    && errno == ELOOP);

	/*
	 * A component of filename does not name an existing file or file_name
	 * points to an empty string.
	 */
	assert(realpath("sandbox/thisdefinitelydoesntexist", actualpath) == NULL
	    && errno == ENOENT);
	assert(realpath("", actualpath) == NULL && errno == ENOENT);

	/* A component of the path prefix is not a directory. */
	assert(realpath("sandbox/notadir/foobar", actualpath) == NULL
	    && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
