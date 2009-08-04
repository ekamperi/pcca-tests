#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

int main(void)
{
	/*
	 * The `tms' structure, which is returned by times(), must be defined,
	 * include at least the following members.
	 */
	struct tms tms;

	(void)tms.tms_utime;	/* User CPU time. */
	(void)tms.tms_stime;	/* System CPU time. */
	(void)tms.tms_cutime;	/* User CPU time of terminated child
				   processes. */
	(void)tms.tms_cstime;	/* System CPU time of terminated child
				   processes. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
