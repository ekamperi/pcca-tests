#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	int detachstate;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract detach state value from attribute object. */
	assert(pthread_attr_getdetachstate(&attr, &detachstate) == 0);

	/* Default value is PTHREAD_CREATE_JOINABLE. */
	assert(detachstate == PTHREAD_CREATE_JOINABLE);

	/* Set detach state. */
	assert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)
	       == 0);
	detachstate = -INT_MAX;		/* Paranoia. */
	assert(pthread_attr_getdetachstate(&attr, &detachstate) == 0);
	assert(detachstate == PTHREAD_CREATE_DETACHED);

	assert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)
	       == 0);
	detachstate = -INT_MAX;		/* Paranoia. */
	assert(pthread_attr_getdetachstate(&attr, &detachstate) == 0);
	assert(detachstate == PTHREAD_CREATE_JOINABLE);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
