#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
	/*
	 * Make sure that the setgid bit is set, the binary belongs to root
	 * group and that we were able to escalate our gid.
	 */
	if (getegid() != 0 ) {
		fprintf(stderr, "WARNING: We were unable to escalate our gid!\n"
                    "WARNING: Make sure that the binary has the setgid bit "
		    "set, the group is root and fs isn't mounted with some "
		    "sort of nosuid option set.\n");
		assert(getegid() == 0);
	}

	/*
	 * Even non-privileged users may set their effective group ID to their
	 * real group ID.
	 *
	 * We use a set gid binary here in order to have distinct
	 * values for egid and rgid. We could mess with setegid() + saved
	 * set-group-ID, but I don't feel like right now.
	 */
	assert(getegid() != getgid());
	assert(setregid(-1, getgid()) == 0);
	assert(getegid() == getgid());

	printf("passed\n");

	return (EXIT_SUCCESS);
}
