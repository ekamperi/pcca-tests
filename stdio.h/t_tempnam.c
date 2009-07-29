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
#include <string.h>	/* strcmp() */

int main(void)
{
        /*
	 * If TMP_MAX is defined, use that unless it exceeds 2000.
	 * We do this because the implementation may support some
	 * astronomically large value and blow up the memory limits.
	 * E.g., in DragonFly it equals 308915776. But, even if
	 * TMP_MAX isn't that large, it still needs to be kept low,
	 * because later on when we check if the generated strings are
	 * unique, we use a nested loop which is of O(n^2) complexity.
	 * And we want the test to complete in reasonable amount of time.
	 */
#ifdef TMP_MAX
	size_t N = TMP_MAX > 2000 ? 2000 : TMP_MAX;
#else
	size_t N = 25;		/* Lowest possible value for TMP_MAX. */
#endif
	char **files;
	size_t i, j;

	/*
	 * Allocate memory for file paths.
	 * We could use a variable-sized array, but let's stick for now
	 * to the C89.
	 */
	files = malloc(N * sizeof(char *));
	assert(files != NULL);

	/* Generate the file paths. */
	for (i = 0; i < N; i++) {
		files[i] = tempnam("/tmp", "file");
		assert(files[i] != NULL);
	}

	/*
	 * Make sure that all generated paths start with our directory,
	 * and contain our prefix.
	 */
	for (i = 0; i < N; i++) {
		assert(strncmp(files[i], "/tmp/", 5) == 0);
		assert(strncmp(files[i] + 5, "file", 4) == 0);
	}

	/*
	 * If the implementation uses tmpnam() internally, we are still
	 * guaranteed at least {TMP_MAX} unique filenames. But, to be
	 * honest, there's no explicit statement for the case where
	 * tempnam() doesn't use tmpnam(). Anyway, tmpfile() shares the
	 * same limit as tmpnam(), so it's reasonable to assume that
	 * tempnam() does the same as well.
	 */
	for (i = 0; i < N-1; i++)
		for (j = i+1; j < N; j++)
			assert(strcmp(files[i], files[j]) != 0);

	/* We are done -- free resouces. */
	for (i = 0; i < N; i++)
		free(files[i]);
	free(files);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
