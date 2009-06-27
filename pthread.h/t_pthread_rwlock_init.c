#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_rwlock_t rwl;

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
