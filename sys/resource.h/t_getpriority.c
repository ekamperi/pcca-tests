#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
	/*
	 * Invalid `which' value.
	 * Since getpriority() may return -1, zero out errno variable
	 * prior to calling it and check it afterwards to distinguish
	 * a legitimate value from a failure.
	 */
	errno = 0;
	assert(getpriority(-112233, 1) == -1 && errno == EINVAL);
	errno = 0;
	assert(getpriority( 112233, 1) == -1 && errno == EINVAL);

	/* Valid `which' value, but no process with `which,who' pair found. */
	errno = 0;
	assert(getpriority(PRIO_USER, -1) == -1 && errno == ESRCH);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
