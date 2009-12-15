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
#include <err.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmpx.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUSERS 10	/* Number of users to simulate. */

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	struct utmpx ut;
	struct utmpx *utp;
	struct stat sb;
	int i, rv;

#undef _PATH_UTMPX
#define _PATH_UTMPX "sandbox/utmpx"

	/* We don't want to leave remnants behind us, if we fail prematurely. */
	signal(SIGABRT, myhandler);

	/*
	 * Make sure that the setuid bit is set, the owner of the binary is root
	 * and that we were able to escalate our uid.
	 * We must run with root privileges, even if we don't modify the real
	 * system-wide utmpx database. Specifically, pututxline() may fail if
	 * done otherwise.
	 */
	if (geteuid() != 0 ) {
		fprintf(stderr, "WARNING: We were unable to escalate our uid!\n"
				"WARNING: Make sure the fs isn't mounted with "
				"some sort of nosuid option set.\n");
		assert(geteuid() == 0);
	}

	/* Make sure there is no other utmpx file flying around. */
	rv = stat(_PATH_UTMPX, &sb);
	assert(rv == -1 && errno == ENOENT);

	/* Create an empty utmpx file. */
	FILE *fp = fopen(_PATH_UTMPX, "w");
	assert(fp != NULL);
	assert(fclose(fp) != EOF);

	/* Populate the utmpx database with artificial entries. */
	for (i = 0; i < NUSERS; i++) {
		/* XXX: How does pututxline() identify a user in database ? */
		memset(&ut, 0, sizeof(ut));

		snprintf(ut.ut_id, sizeof(ut.ut_id), "X%u", i);
		strncpy(ut.ut_user, "user", sizeof(ut.ut_user));
		strncpy(ut.ut_line, "tty", sizeof(ut.ut_line));
		strncpy(ut.ut_host, "voyager", sizeof(ut.ut_host));
		ut.ut_type = USER_PROCESS;
		ut.ut_pid = i;

		/* Update the utmpx database. */
		assert(pututxline(&ut) != NULL);
	}

	/*
	 * Reset utmpx database, so that the next getutxent() call will get the
	 * first entry. Closing the database and deferring to getutxent() the
	 * responsibility to open it, would have the same effect.
	 */
	setutxent();

	/* Loop through the whole utmpx database. */
	for (i = 0; i < NUSERS; i++) {
		/*
		 * getutxent() may fail if the end of utmpx database has been
		 * reached (which is clearly not the case here, since we read
		 * exactly as many entries as we write), or due to problems
		 * reading from database. That's why, treat errors as fatal.
		 */
		utp = getutxent();
		assert(utp != NULL);

		/* Verify entries. */
		snprintf(ut.ut_id, sizeof(ut.ut_id), "X%u", i);
		assert(strcmp(utp->ut_id, ut.ut_id) == 0);
		assert(strcmp(utp->ut_user, "user") == 0);
		assert(strcmp(utp->ut_line, "tty") == 0);
		assert(strcmp(utp->ut_host, "voyager") == 0);
		assert(utp->ut_type == USER_PROCESS);
	}

	/* Close database. */
	endutxent();

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	unlink(_PATH_UTMPX);
}
