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
	int rv;

	/* A component of path prefix denies search permission. */
	rv = link("sandbox/dir666/whatever", "sandbox/whatever");
	assert(rv == -1 && errno == EACCES);

	/*
	 * The requested link requires writing in a directory that denies
	 * write permission.
	 */
	rv = link("sandbox/file777", "sandbox/dir555/whatever");
	assert(rv == -1 && errno == EACCES);

	/* The `path2' argument resolves to an existing file. */
	rv = link("sandbox/file777", "sandbox/file777");
	assert(rv == -1 && errno == EEXIST);

	/* The `path2' argument' refers to a symbolic link. */
	rv = link("sandbox/file777", "sandbox/fileloop");
	assert(rv == -1 && errno == EEXIST);

#ifdef NOTYET
	/*
	 * A loop exists in symbolic links encountered during resolution
	 * of the path1 or path2 argument.
	 */
	rv = link("sandbox/infloop", "sandbox/whatever");
	assert(rv == -1 && errno == ELOOP);

	rv = link("sandbox/file777", "sandbox/infloop");
	assert(rv == -1 && errno == ELOOP);
#endif

	/* XXX: Add test for ENAMETOOLONG. */

	/* A component of either path prefix is not a directory. */
	rv = link("sandbox/notadir/whatever", "sandbox/whatever");
	assert(rv == -1 && errno == ENOTDIR);

	rv = link("sandbox/file777", "sandbox/notadir/whatever");
	assert(rv == -1 && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
