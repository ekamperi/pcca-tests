#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_barrierattr_t pba;
	int sharedval;

	/* Initialize barrier attribute object. */
	assert(pthread_barrierattr_init(&pba) == 0);

	/* Get the process shared attribute value. */
	assert(pthread_barrierattr_getpshared(&pba, &sharedval) == 0);

	/* By default this is set to PTHREAD_PROCESS_PRIVATE. */
	assert(sharedval == PTHREAD_PROCESS_PRIVATE);

	/* Destroy barrier attribute object. */
	assert(pthread_barrierattr_destroy(&pba) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
