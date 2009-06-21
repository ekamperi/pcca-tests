#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int rv, rv2;

        /*
	 * Try to lower our nice value (thus go to a more favorable
         * scheduling), without being privileged (root?).
	 */
        rv = nice(-2);
        assert(rv == -1 && errno == EPERM);

	/*
	 * nice(3) may return -1 as a legitimate nice value.
	 * In that case though, errno isn't touched.
	 */
	errno = 0;
	rv = nice(0);
	assert(rv != -1 || errno == 0);

	/* Increasing our nice value doesn't require spectacular privileges. */
	rv2 = nice(1);
	assert(rv2 != -1 || errno == 0);
	assert(rv2 == rv + 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
