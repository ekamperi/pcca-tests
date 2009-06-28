#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_condattr_t attr;
	int pshared;

	/* Initialize condition variable attributes object. */
	assert(pthread_condattr_init(&attr) == 0);

	/* Extract the shared attribute value. */
	assert(pthread_condattr_getpshared(&attr, &pshared) == 0);

	/* By default this is set to PTHREAD_PROCESS_PRIVATE. */
	assert(pshared == PTHREAD_PROCESS_PRIVATE);

	/* Destroy condition variable attributes object. */
	assert(pthread_condattr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
