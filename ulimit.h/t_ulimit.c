#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <ulimit.h>

int main(void)
{
	long rv;

	/*
	 * We expect this simple call to succeed.  All return values are
	 * permissible in a successful situation, including -1 (?).
	 */
	errno = 0;
	rv = ulimit(UL_GETFSIZE);
	assert(rv != -1 || errno == 0);

        /*
	 * Try to increase our file size limit, without being privileged.
	 * Make sure we don't overflow though.
	 */
	if (rv + 1 > rv) {
		errno = 0;
		rv = ulimit(UL_SETFSIZE, rv + 1);
		assert(rv == -1 && errno == EPERM);
	}

	/* Try to lower our file size limit. */
	errno = 0;
	rv = ulimit(UL_SETFSIZE, 0);
	assert(rv != -1 || errno == 0);

	/* Invalid cmd argument. */
	rv = ulimit(-INT_MAX);
	assert(rv == -1 && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
