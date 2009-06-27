#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(void)
{
	pthread_rwlock_t rwl;
	struct timespec abs;
	struct timeval now;

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire read lock. */
	assert(pthread_rwlock_rdlock(&rwl) == 0);
	assert(pthread_rwlock_rdlock(&rwl) == 0);
	assert(pthread_rwlock_rdlock(&rwl) == 0);

	/* Try to acquire a write lock. */
	abs.tv_sec = 0;
	abs.tv_nsec = 0;
	assert(pthread_rwlock_timedwrlock(&rwl, &abs) == ETIMEDOUT);

	assert(gettimeofday(&now, NULL) == 0);
	abs.tv_sec = now.tv_sec + 2;
	abs.tv_nsec = 1000 * now.tv_usec;
	assert(pthread_rwlock_timedwrlock(&rwl, &abs) == ETIMEDOUT);

	assert(pthread_rwlock_unlock(&rwl) == 0);
	assert(pthread_rwlock_unlock(&rwl) == 0);
	assert(pthread_rwlock_unlock(&rwl) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
