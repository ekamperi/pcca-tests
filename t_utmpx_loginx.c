#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libutil.h>
#include <utmpx.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
	struct utmpx myent;
	struct utmpx *rv;
	struct stat sb;

	/* There must exist a /var/run/utmpx file. */
	if (stat(_PATH_UTMPX, &sb) == -1) {
		if (errno == ENOENT) {
			errx(EXIT_FAILURE,
			    "there must exist a /var/run/utmpx file");
		}
	}

	/* Zero out the utmpx structure. */
	bzero(&myent, sizeof(myent));

	/* Populate the utmpx structure. */
	strcpy(myent.ut_name, "t_utmpx_loginx");
	strcpy(myent.ut_id, "10");
	strcpy(myent.ut_line, "ttyv0");
	strcpy(myent.ut_host, "voyager");
	myent.ut_type = LOGIN_PROCESS;

	/* Update database. */
	loginx(&myent);

	/* Close database. */
	endutxent();

	/*
	 * Get next entry from database;
	 * since we just closed it, getutexnt(3) will reopen it.
	*/
	rv = getutxent();
	assert(rv != NULL);
	assert(strcmp(rv->ut_name, "t_utmpx_loginx") == 0);
	assert(strcmp(rv->ut_id, "10") == 0);
	assert(strcmp(rv->ut_line, "ttyv0") == 0);
	assert(strcmp(rv->ut_host, "voyager") == 0);
	assert(rv->ut_type == LOGIN_PROCESS);

	/* Close database. */
	endutxent();

	printf("passed\n");

	return (EXIT_SUCCESS);
}
