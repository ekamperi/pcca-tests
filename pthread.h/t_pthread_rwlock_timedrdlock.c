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
	struct timespec abstime;
	struct timeval now;

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire write lock. */
	assert(pthread_rwlock_wrlock(&rwl) == 0);

	/* Try to acquire a read lock. */
	abstime.tv_sec = 0;
	abstime.tv_nsec = 0;
	assert(pthread_rwlock_timedrdlock(&rwl, &abstime) == ETIMEDOUT);

	assert(gettimeofday(&now, NULL) == 0);
	abstime.tv_sec = now.tv_sec + 2;
	abstime.tv_nsec = 1000 * now.tv_usec;
	assert(pthread_rwlock_timedrdlock(&rwl, &abstime) == ETIMEDOUT);

	assert(pthread_rwlock_unlock(&rwl) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
