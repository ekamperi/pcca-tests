#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(void)
{
	/*
	 * The `timeval' structure must be defined, including at least
	 * the following members.
	 */
	struct timeval tv;

	(void)tv.tv_sec;	/* Seconds. */
	(void)tv.tv_usec;	/* Microseconds. */

	/*
	 * XXX: This is marked as obsolete in Issue 6.
	 * The `itimerval' structure must be defined, including at least
	 * the following members.
	 */
	struct itimerval it;

	(void)it.it_interval;	/* Timer interval. */
	(void)it.it_value;	/* Current value. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
