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
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	BUFSIZE	1024

int main(void)
{
	char buf[BUFSIZE + 1];	/* Reserve space for '\0' */

	/* Zero out buffer. */
	memset(buf, 0, BUFSIZE + 1);

	/*
	 * POSIX allows basename() to modify the string pointed to by path.
	 * Therefore, avoid passing string literals, as they are non-writeable.
	 */
	strncpy(buf, "/usr/lib", BUFSIZE);
	assert(strcmp(basename(buf), "lib") == 0);

	strncpy(buf, "/usr/", BUFSIZE);
	assert(strcmp(basename(buf), "usr") == 0);

	strncpy(buf, "/", BUFSIZE);
        assert(strcmp(basename(buf), "/") == 0);

	strncpy(buf, "///", BUFSIZE);
        assert(strcmp(basename(buf), "/") == 0);

	strncpy(buf, "//usr//lib//", BUFSIZE);
        assert(strcmp(basename(buf), "lib") == 0);

	strncpy(buf, "", BUFSIZE);
	assert(strcmp(basename(buf), ".") == 0);

	assert(strcmp(basename(NULL), ".") == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
