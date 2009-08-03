#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `passwd' structure maste be defined, including at least
	 * the following members.
	 */
	struct passwd pw;

	(void)pw.pw_name;	/* User's login name. */
	(void)pw.pw_uid;	/* Numerical user ID. */
	(void)pw.pw_gid;	/* Numerical group ID. */
	(void)pw.pw_dir;	/* Initial working directory. */
	(void)pw.pw_shell;	/* Program to use as shell. */

	/*
	 * The `gid_t' and `uid_t' types must be defined.
	 * (see <sys/types.h>)
	 */
	gid_t g;
	uid_t u;

	g = u = 1;	/* To silence gcc warning. */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
