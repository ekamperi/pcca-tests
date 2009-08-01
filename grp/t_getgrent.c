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

#define _XOPEN_SOURCE 600

#include <assert.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct group *pgr;
	size_t i, j;

	/*
	 * Loop over the group database. The first getgrent() call returns the
	 * first entry and subsequent calls return the rest of the entries.
	 */
	i = 0;
	while((pgr = getgrent()) != NULL) {
		/*printf("%s\n", pgr->gr_name);*/
		i++;
	}

	/* Rewind the group database to the beginning of it. */
	setgrent();

	/* And loop over again until the end of it. */
	j = 0;
        while((pgr = getgrent()) != NULL)
		j++;

	/* The 2 numbers must be in agreement. */
	assert(i == j);

	/* Close the group database. */
	endgrent();

	/*
	 * Reopening the group database via getgrent(), must automatically
	 * rewind it.
	 */
        j = 0;
        while((pgr = getgrent()) != NULL)
                j++;

	/* The 2 numbers must be in agreement. */
	assert(i == j);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
