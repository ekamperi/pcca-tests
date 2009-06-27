#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int isdeadlock = 1;

/* Function prototypes. */
static void *deadthread(void *);

int main(void)
{
	pthread_t deadtid;

	/* Create thread. */
	assert(pthread_create(&deadtid, NULL, deadthread, (void *)NULL) == 0);

	/*
	 * We can't call pthread_join(), because we don't know whether the
	 * implementation supports deadlock detection. Instead, we sleep for
	 * 1 second.
	 */
	sleep(1);

	assert(!isdeadlock);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
deadthread(void *arg)
{
        pthread_rwlock_t rwl;

        /* Create read-write lock with default parameters. */
        assert(pthread_rwlock_init(&rwl, NULL) == 0);

	/* Acquire a read lock, followed by a write lock. */
        assert(pthread_rwlock_rdlock(&rwl) == 0);
        assert(pthread_rwlock_wrlock(&rwl) == EDEADLK);

	/* Release read lock. */
	assert(pthread_rwlock_unlock(&rwl) == 0);

        /* Destroy read-write lock. */
        assert(pthread_rwlock_destroy(&rwl) == 0);

	isdeadlock = 0;

	pthread_exit(NULL);
}
