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
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function prototypes. */
int mystrcmp(const void *s1, const void *s2);

int main(void)
{
	const char *array[] = { "this", "is", "an", "array", "with", "words" };
	size_t i, n, n_orig;
	const char *key;

	/* Number of elements in array. */
	n = sizeof(array) / sizeof(*array);
	n_orig = n;

	for (i = 0; i < n; i++) {
		/* What key to search for. */
		key = array[i];

		assert(lfind(&key, array, &n, sizeof(char *), mystrcmp)
		    != NULL);
	}

	/* Key doesn't exist in array. */
	key = "nonexistentkey";
	assert(lfind(&key, array, &n, sizeof(char *), mystrcmp) == NULL);

	/*
	 * Just a sanity check that lfind doesn't alter the number of elements.
	 * (lsearch which does, increments the integer passed to it)
	 */
	assert(n == n_orig);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

int mystrcmp(const void *s1, const void *s2)
{
#if 0
	printf("s1 = %s\ts2 = %s\n",
	    *(const char **)s1,
	    *(const char **)s2);
#endif

	return (strcmp(*(const char **)s1, *(const char **)s2));
}
