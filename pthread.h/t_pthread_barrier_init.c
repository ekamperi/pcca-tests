#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_barrier_t pb;

	/* Count argument is zero. */
	assert(pthread_barrier_init(&pb, NULL, 0) == EINVAL);

	/* We expect these simple calls to succeed. */
	assert(pthread_barrier_init(&pb, NULL, 2) == 0);
	assert(pthread_barrier_destroy(&pb) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
