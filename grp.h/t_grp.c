#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*
	 * The `group' structure must be defined, including the following
	 * members:
	 */
	struct group gr;

	(void)gr.gr_name;	/* The name of the group. */
	(void)gr.gr_gid;	/*  Numerical group ID. */
	(void)gr.gr_mem;	/* Pointer to a null-terminated array of char
				   pointers to member names. */

	/*
	 * The `gid_t' type must be defined as an integer type.
	 * (see <sys/types.h>.
	 */
	gid_t gid;
	gid = -1;

	printf("passed\n");

	return (EXIT_SUCCESS);
}
