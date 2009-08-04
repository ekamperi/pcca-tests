#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{

	/*
	 * The `tm' structure must be defined, including at least
	 * the following members.
	 */
	struct tm tm;

	(void)tm.tm_sec;	/* Seconds [0,60]. */
	(void)tm.tm_min;	/* Minutes [0,59]. */
	(void)tm.tm_hour;	/* Hour [0,23]. */
	(void)tm.tm_mday;	/* Day of month [1,31]. */
	(void)tm.tm_mon;	/* Month of year [0,11]. */
	(void)tm.tm_year;	/* Years since 1900. */
	(void)tm.tm_wday;	/* Day of week [0,6] (Sunday =0). */
	(void)tm.tm_yday;	/* Day of year [0,365]. */
	(void)tm.tm_isdst;	/* Daylight Savings flag. */

	/*
	 * The `itimerspec' structure must be defined, including at least
	 * the following members.
	 */
	struct itimerspec it;

	(void)it.it_interval;	/* Timer period. */
	(void)it.it_value;	/* Timer expiration. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
