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
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

int main(int argc, char *argv[])
{
	char *p;
	size_t sz = 4096;	/* Default value for PATH_MAX */

	/* Exceed maximum path length limit. */
#ifdef	_PC_PATH_MAX
	/* Determine maximum path length. */
	sz = pathconf(".", "_PC_PATH_MAX");
	assert(sz != -1);
#endif
	p = malloc(sz + 1);
	assert(p != NULL);
	memset(p, 0xff, sz + 1);	/* Make sure we don't terminate early.*/
	assert(opendir(p) == NULL && errno == ENAMETOOLONG);
	free(p);

	/* Directory doesn't exist. */
	assert(opendir("/this/certainly/shouldn/t/exist") == NULL && errno == ENOENT);

	/* Try to open something that isn't a dir. */
	assert(opendir(argv[0]) == NULL && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
