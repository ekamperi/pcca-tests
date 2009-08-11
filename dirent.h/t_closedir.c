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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void myhandler(int );

int main(void)
{
	DIR *dirp;

	/* We expect this simple operation to succeed. */
	assert((dirp = opendir(".")) != NULL);
	assert(closedir(dirp) == 0);

	/*
	 * XXX: The following test must always be the last one to run.
	 *
	 * POSIX suggests that if the supplied argument of closedir(3) doesn't
	 * refer to an open directory stream, EBADF _may_ be returned. Some
	 * operating systems don't and the test case dies with segmentation
	 * fault. Catch SIGSEGV , because otherwise the false impression of
	 * the test case being flawed is given to the user.
	 */
	signal(SIGSEGV, myhandler);

	/* Bad directory stream. */
	assert(closedir(NULL) == 0 && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	/* Ignore subsequent occurences of the signal. */
	signal(sig, SIG_IGN);

	printf("passed (EBADF check was skipped)\n");
	exit(EXIT_SUCCESS);
}
