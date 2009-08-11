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
#include <limits.h>	/* for OPEN_MAX */
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static int mycallback(const char *, const struct stat *, int);

int main(int argc, char *argv[])
{
	/* ndirs isn't in the range [1, {OPEN_MAX}] */
	assert(ftw(".", mycallback, 0) == -1 && errno == EINVAL);
#ifdef OPEN_MAX
	assert(ftw(".", mycallback, OPEN_MAX + 1) == -1 && errno == EINVAL);
#endif

	/* Inexistent path. */
	assert(ftw("", mycallback, 1) == -1 && errno == ENOENT);
	assert(ftw("/sandbox/thisdefinitelydoesntexist", mycallback, 1) == -1 &&
	       errno == ENOENT);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static int
mycallback(const char *path, const struct stat *pstat, int flag)
{
	/* printf("%s\n", path); */

	return 0;
}
