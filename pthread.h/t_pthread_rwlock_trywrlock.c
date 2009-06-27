#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_rwlock_t rwl;

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire read lock. */
	assert(pthread_rwlock_rdlock(&rwl) == 0);

	/* Try to acquire write lock. */
	assert(pthread_rwlock_trywrlock(&rwl) == EBUSY);

	/* Release read lock. */
	assert(pthread_rwlock_unlock(&rwl) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
