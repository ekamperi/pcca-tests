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
	struct utmpx myent;
	struct utmpx *rv;
	struct stat sb;
	size_t i;

	/* It must be run with root privileges. */
	if (geteuid() != 0) {
		errx(EXIT_FAILURE,
		    "it must be run with root privileges");
	}

	/*
	 * There must exist a /var/run/utmpx file.
	 * Subsequent calls will overwrite existing user entries in utmpx
	 * database, so there is no need to be empty at the first place.
	 */
	if (stat(_PATH_UTMPX, &sb) == -1) {
		if (errno == ENOENT) {
			errx(EXIT_FAILURE,
			    "there must exist a /var/run/utmpx file");
		}
	}

	for (i = 0; i < NUSERS; i++) {
		/* XXX: how does pututxline() identify a user in database ? */
                memset(&myent, 0, sizeof(myent));

                snprintf(myent.ut_id, sizeof(myent.ut_id), "X%u", i);
		strncpy(myent.ut_name, "user", sizeof(myent.ut_name));
		strncpy(myent.ut_line, "tty", sizeof(myent.ut_line));
		strncpy(myent.ut_host, "voyager", sizeof(myent.ut_host));
		myent.ut_type = USER_PROCESS;
		myent.ut_pid = i;

		/* Update database. */
		assert(pututxline(&myent) != NULL);
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
