#include <stdio.h>
#include <stdlib.h>
#if defined(_NETBSD_SOURCE)
#include <util.h>
#else
#include <libutil.h>
#endif
#include <utmpx.h>

int main(void)
{
	struct utmpx ut;
	FILE *fp;

	/* Open utmpx database. */
	fp = fopen(_PATH_UTMPX, "ro");
	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	/* Loop over the whole database. */
	while (!feof(fp)) {
		if (fread(&ut, sizeof(ut), 1, fp) < 1  && !feof(fp)) {
			perror("fread");
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		printf("ut_name = %s\tut_id = %s\tut_line = %s\tut_host = %s\n",
		    ut.ut_name, ut.ut_id, ut.ut_line, ut.ut_host);
	}

	/* Close database. */
	fclose(fp);

	return (EXIT_SUCCESS);
}
