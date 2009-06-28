#include <assert.h>
#include <errno.h>
#include <time.h>	/* for CLOCK_REALTIME */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_condattr_t attr;
	clockid_t clockid;

	/* Initialize condition variable attributes object. */
	assert(pthread_condattr_init(&attr) == 0);

	/* Extract the clockid attribute value. */
	assert(pthread_condattr_getclock(&attr, &clockid) == 0);

	/* By default this is set to CLOCK_REALTIME. */
	assert(clockid == CLOCK_REALTIME);

	/* Destroy condition variable attributes object. */
	assert(pthread_condattr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
