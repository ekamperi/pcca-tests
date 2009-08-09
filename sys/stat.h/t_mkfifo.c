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
#include <sys/stat.h>

int main(void)
{
	int rv;

	/*
	 * A component of the path prefix denies search permission, or write
	 * permission is denied on the parent directory of the FIFO to be created.
	 */
	rv = mkfifo("sandbox/dir666/whatever", S_IRWXU);
	assert(rv == -1 && errno == EACCES);

	rv = mkfifo("sandbox/dir000/whatever", S_IRWXU);
	assert(rv == -1 && errno == EACCES);

	/* The named file already exists. */
	rv = mkfifo("sandbox/file777", S_IRWXU);
	assert(rv == -1 && errno == EEXIST);

	/*
	 * A loop exists in symbolic links encountered during resolution of
	 * the path argument.
	 */
	rv = mkfifo("sandbox/infloop/whatever", S_IRWXU);
	assert(rv == -1 && errno == ELOOP);

	/* XXX: ENAMETOOLONG */

	/*
	 * A component of the path prefix specified by path does not name an
	 * existing directory or path is an empty string.
	 */
	rv = mkfifo("sandbox/doesntexist/whatever", S_IRWXU);
	assert(rv == -1 && errno == ENOENT);

	rv = mkfifo("", S_IRWXU);
	assert(rv == -1 && errno == ENOENT);

	/* A component of the path prefix is not a directory. */
	rv = mkfifo("sandbox/notadir/whatever", S_IRWXU);
	assert(rv == -1 && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
