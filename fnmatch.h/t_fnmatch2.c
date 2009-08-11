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
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
 
int main(void)
{
	DIR *dirp;
	struct dirent *dp;
	const char *pattern;
	int dot, dotdot, rv;

	/* Open directory stream. */
	dirp = opendir(".");
	assert(dirp != NULL);


	/* Scan directory and match . and .. */
	dot = 0;
	dotdot = 0;
	while ((dp = readdir(dirp)) != NULL) {
		/* First */
		pattern = ".";
		rv = fnmatch(pattern, dp->d_name, 0);
		if (rv == 0) {
			dot++;
		} else {
			/* It either matches, or not. The rest are errors. */
			assert(rv == FNM_NOMATCH);
		}

		/* Second */
		pattern = "..";
		rv = fnmatch(pattern, dp->d_name, 0);
		if (rv == 0) {
			dotdot++;
		} else {
			/* It either matches, or not. The rest are errors. */
			assert(rv == FNM_NOMATCH);
		}
	}

	/* Close directory stream. */
	assert(closedir(dirp) == 0);

	/* Make sure we match _exactly one_ for both of them. */
	assert(dot == 1 && dotdot == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
