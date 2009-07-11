#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	gid_t *pgroups;
	int ngroups;

	/*
	 * Get the number of supplementary group IDs we belong to.
	 *
	 * Every user belongs to a primary group which is defined via her/his
	 * gid in /etc/passwd. A user may be listed as member of other groups as
	 * well in /etc/group. THe latter are the supplementary groups.
	 */
	ngroups = getgroups(0, NULL);

	if (ngroups > 0) {
		pgroups = malloc(ngroups * sizeof(gid_t));
		assert(pgroups != NULL);

		/* Get the actual supplementary group IDs we belong to. */
		assert(getgroups(ngroups, pgroups) == ngroups);

		/*
		 * The size is non-zero and less than the number of group IDs
		 * that would have been returned.
		 */
		if (ngroups > 1)
			assert(getgroups(1, pgroups) == -1 && errno == EINVAL);
	}

	printf("passed\n");

	return (EXIT_SUCCESS);
}
