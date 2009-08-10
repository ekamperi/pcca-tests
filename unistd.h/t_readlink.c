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
#include <string.h>	/* memset() */
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buf[4096];

	/* We are not a symbolic link. */
	assert(readlink(argv[0], buf, sizeof(buf) - 1) == -1 && errno == EINVAL);

	/* Provide invalid path to link. */
	assert(readlink("", buf, sizeof(buf) - 1) == -1 && errno == ENOENT);
	assert(readlink("/this/really/shouldn/t/exist",
			buf, sizeof(buf) - 1 == -1 && errno == ENOENT));

	/* XXX: Exceed maximum path length. */
	char *p;
	p = malloc(32768);
	assert(p != NULL);
	memset(p, 0xff, 32768);	/* Make sure we don't terminate prematurely. */
	assert(readlink(p, buf, sizeof(buf) - 1 == -1 && errno == ENAMETOOLONG));
	free(p);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
