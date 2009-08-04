#include <stdio.h>
#include <stdlib.h>
#include <utime.h>

int main(void)
{
	/*
	 * The `utimbuf' structure must be defined, including the
	 * following members.
	 */
	struct utimbuf ut;

	(void)ut.actime;	/* Access time. */
	(void)ut.modtime;	/* Modification time. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
