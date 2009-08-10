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
#include <unistd.h>

int main(void)
{
	gid_t *pgroups;
	int ngroups;

	/*
	 * Get the number of supplementary group IDs we belong to.
	 *
	 * Every user belongs to a primary group which is defined via her/his
	 * gid in /etc/passwd. A user may be listed as member of other groups as
	 * well in /etc/group. THe latter are the supplementary groups.
	 */
	ngroups = getgroups(0, NULL);

	if (ngroups > 0) {
		pgroups = malloc(ngroups * sizeof(gid_t));
		assert(pgroups != NULL);

		/* Get the actual supplementary group IDs we belong to. */
		assert(getgroups(ngroups, pgroups) == ngroups);

		/*
		 * The size is non-zero and less than the number of group IDs
		 * that would have been returned.
		 */
		if (ngroups > 1)
			assert(getgroups(1, pgroups) == -1 && errno == EINVAL);

		free(pgroups);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
