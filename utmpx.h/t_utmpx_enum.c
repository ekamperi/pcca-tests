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
#include <stdio.h>
#include <stdlib.h>
#if defined(_NETBSD_SOURCE)
#include <util.h>
#else
#include <libutil.h>	/* for DragonFly */
#endif
#include <utmpx.h>

int main(void)
{
	struct utmpx ut;
	FILE *fp;

	/* Open utmpx database. */
	fp = fopen(_PATH_UTMPX, "r");
	assert(fp != NULL);

	/* Loop over the whole database. */
	while (!feof(fp)) {
		if (fread(&ut, sizeof(ut), 1, fp) < 1) {
			/*
			 * The only valid reason that could bring us here is,
			 * if we have reached the end of the database file.
			 */
			assert(feof(fp));
		} else {
#ifdef thisisatest
			printf("ut_name = %-20s\tut_id = %-20s\t"
			    "ut_line = %-20s\tut_host = %s\n",
			    ut.ut_name, ut.ut_id, ut.ut_line, ut.ut_host);
#endif
		}
	}

	/* Close database. */
	assert(fclose(fp) != EOF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
