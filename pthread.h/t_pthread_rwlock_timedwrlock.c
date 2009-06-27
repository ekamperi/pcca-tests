#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

pthread_rwlock_t rwl;

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t tid;

	/* Create read-write lock with default parameters. */
	assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire read lock. */
	assert(pthread_rwlock_rdlock(&rwl) == 0);
	assert(pthread_rwlock_rdlock(&rwl) == 0);
	assert(pthread_rwlock_rdlock(&rwl) == 0);

	/* Create thread. */
	assert(pthread_create(&tid, NULL, thread, (void *)NULL) == 0);

	/* Wait for thread to complete. */
	assert(pthread_join(tid, NULL) == 0);

	/* Release read lock. */
	assert(pthread_rwlock_unlock(&rwl) == 0);
	assert(pthread_rwlock_unlock(&rwl) == 0);
	assert(pthread_rwlock_unlock(&rwl) == 0);

	/* Destroy read-write lock. */
	assert(pthread_rwlock_destroy(&rwl) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
        struct timespec abstime;
        struct timeval now;

	/* Try to acquire a write lock. */
	abstime.tv_sec = 0;
	abstime.tv_nsec = 0;
	assert(pthread_rwlock_timedwrlock(&rwl, &abstime) == ETIMEDOUT);

	assert(gettimeofday(&now, NULL) == 0);
	abstime.tv_sec = now.tv_sec + 2;
	abstime.tv_nsec = 1000 * now.tv_usec;
	assert(pthread_rwlock_timedwrlock(&rwl, &abstime) == ETIMEDOUT);

	pthread_exit(NULL);
}
