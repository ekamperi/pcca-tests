#define XOPEN_SOURCE 600

#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int
main(void)
{
	/* Get real and effective group ID. */
	gid_t rgid = getgid();
	gid_t egid = getegid();

	/* This shouldn't change neither real nor effective group ID. */
	assert(setregid(-1, -1) == 0);
	assert(getgid() == rgid);
	assert(getegid() == egid);

	/*
	 * Try to change the real group ID and effective group ID without
	 * being privileged enough. We hope that increasing the old values
	 * by 1, will result in a valid group ID.
	 */
	assert(setregid(rgid + 1, egid + 1) == -1 && errno == EPERM);

	/*
	 * After a failed call to setregid() neither of the group IDs are
	 * changed.
	 */
	assert(getgid() == rgid);
	assert(getegid() == egid);

	/*
	 * Invalid value of real and effective group ID.
	 *
	 * But since we are not privileged, we may fail with EPERM before the
	 * values reach the validation code! POSIX doesn't say which one takes
	 * precedence over the other.
	 */
	assert(setregid(-INT_MAX, -INT_MAX) == -1 &&
	    (errno == EINVAL || errno == EPERM));

	/*
	 * After a failed call to setregid() neither of the group IDs are
	 * changed.
	 */
	assert(getgid() == rgid);
	assert(getegid() == egid);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
