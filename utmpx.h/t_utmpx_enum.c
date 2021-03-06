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
#include <stdio.h>
#include <stdlib.h>
#include <utmpx.h>

int
main(void)
{
	struct utmpx ut;
	FILE *fp;

	/* Determine the path of the utmpx database file. */
#if defined (__SVR4) && defined (__sun)
	/*
	 * In OpenSolaris /etc/utmpx is a symlink to /var/adm/utmpx.
	 */
	#define MY_UTMPX_PATH "/var/adm/utmpx"
#elif defined(__linux)
	/*
	 * Linux defines the utmpx structure to be the same as the utmp
	 * structure.
	 */
	#define MY_UTMPX_PATH "/var/run/utmp"
#else
	/* Default case. */
	#define MY_UTMPX_PATH "/etc/utmpx"
#endif

	/* Open utmpx database. */
	fp = fopen(MY_UTMPX_PATH, "r");
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
		  /* Do some silly checks. */
		  assert(sizeof(ut.ut_pid) == sizeof(pid_t));
		  assert(sizeof(ut.ut_type) == sizeof(short));
		  assert(sizeof(ut.ut_tv) == sizeof(struct timeval));

#if 0
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
