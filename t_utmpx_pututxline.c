#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libutil.h>
#include <utmpx.h>

#define NUSERS 10	/* Number of users to simulate. */

int main(void)
{
	struct utmpx ut;
	struct utmpx *rv;
	struct stat sb;
	size_t i;

	/* It must be run with root privileges. */
	if (geteuid() != 0) {
		errx(EXIT_FAILURE,
		    "it must be run with root privileges");
	}

	/* There must exist an empty utmpx file. */
	if (stat(_PATH_UTMPX, &sb) == -1) {
		if (errno == ENOENT) {
			errx(EXIT_FAILURE,
			    "there must exist an empty " _PATH_UTMPX " file");
		}
	} else {
		if (sb.st_size != 0)
			errx(EXIT_FAILURE, _PATH_UTMPX " must be empty");
	}

	for (i = 0; i < NUSERS; i++) {
		/* XXX: how does pututxline() identify a user in database ? */
                memset(&ut, 0, sizeof(ut));

                snprintf(ut.ut_id, sizeof(ut.ut_id), "X%u", i);
		strncpy(ut.ut_name, "user", sizeof(ut.ut_name));
		strncpy(ut.ut_line, "tty", sizeof(ut.ut_line));
		strncpy(ut.ut_host, "voyager", sizeof(ut.ut_host));
		ut.ut_type = USER_PROCESS;
		ut.ut_pid = i;

		/* Update database. */
		assert(pututxline(&ut) != NULL);
	}

	/*
	 * Reset utmpx database, so that the next getutxent() call  will get the
	 * first entry. Closing the database and deferring to getutxent() the
	 * responsibility to open it, would have the same effect.
	 */
	setutxent();

	/* Loop through the whole utmpx database. */
	for (i = 0; i < NUSERS; i++) {
		/* getutxent() might fail if the end of utmpx database has been
		 * reached (which is clearly not the case here, since we read
		 * exactly as many entries as we write), or due to problems
		 * reading from database. That's why, treat errors as fatal.
		 */
		rv = getutxent();
		assert(rv != NULL);

		/* Verify entries. */
		snprintf(ut.ut_id, sizeof(ut.ut_id), "X%u", i);
		assert(strcmp(rv->ut_id, ut.ut_id) == 0);
		assert(strcmp(rv->ut_name, "user") == 0);
		assert(strcmp(rv->ut_line, "tty") == 0);
		assert(strcmp(rv->ut_host, "voyager") == 0);
		assert(rv->ut_type == USER_PROCESS);
	}

	/* Close database. */
	endutxent();

	printf("passed\n");

	return (EXIT_SUCCESS);
}
