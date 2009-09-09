#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <utmpx.h>

int main(void)
{
	struct utmpx ut;

	/* POSIX mandates the following structure members. */
	(void)ut.ut_user;	/* User login name */
	(void)ut.ut_id;		/* Unspecified init proc id */
	(void)ut.ut_line;	/* Device name */
	(void)ut.ut_pid;	/* Process ID */
	(void)ut.ut_type;	/* Type of entry */
	(void)ut.ut_tv;		/* Time entry was made */

	printf("passed\n");
	
	return (EXIT_SUCCESS);
}
