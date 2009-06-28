#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_condattr_t attr;

	/* Initialize condition variable attributes object. */
	assert(pthread_condattr_init(&attr) == 0);

	/* Destroy condition variable attributes object. */
	assert(pthread_condattr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
