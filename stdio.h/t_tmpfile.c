/*
 * Copyright (c) 2009, Stathis Kamperis
 * All rights reserved.

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
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
#ifdef FOPEN_MAX
	/*
	 * FOPEN_MAX is normally bounded by OPEN_MAX,
	 * so we are not worried about coming up with
	 * some ridiculously large value.
	 */
	size_t N = FOPEN_MAX;
#else
	size_t N = 8;	/* Least possible value for FOPEN_MAX */
#endif
	struct stat sb;
	FILE **fp;
	size_t i;

	/* Allocate memory for FILE* */
	fp = malloc(N * sizeof(FILE *));
	assert(fp != NULL);

	/* Create as much temporary files us possible. */
	for (i = 0; i < N; i++) {
		fp[i] = tmpfile();
		assert(fp[i] != NULL);
	}

	/*
	 * POSIX says that the file created by tmpfile() must be automatically
	 * deleted when all refs to the file are closed.
	 *
	 * Now, according to unlink() when a file's link count drops to 0 and
	 * no process has the file open, the file becomes inaccessible. But if
	 * one or more processes have the file open when the last link is
	 * removed, the removal of the file contents is delayed up until all
	 * refs to the file are closed. This is a clear distincition between
	 * link cound and reference count.
	 *
	 * For an implementation to be consistent with this, the link count
	 * of the file must be 0 when tmpfile() returns. The temporary file
	 * will still be accessible, because we (as a process) are still alive.
	 * When we will terminate, the file will be garbage collected.
	 */
	for (i = 0; i < N; i++) {
		assert(fstat(fileno(fp[i]), &sb) != -1);
		assert(sb.st_nlink == 0);
	}

	/* Free up the resources. */
	free(fp);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
