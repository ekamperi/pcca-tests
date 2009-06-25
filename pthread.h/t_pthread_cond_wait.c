#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	pthread_cond_t cond;
	pthread_mutex_t mtx;
	struct timespec abstime;

	/* Create a condition variable with default attributes. */
	assert(pthread_cond_init(&cond, NULL) == 0);

	/* Initialize mutex. */
	assert(pthread_mutex_init(&mtx, NULL) == 0);

	/* Acquire lock. */
	assert(pthread_mutex_lock(&mtx) == 0);

	/* Invalid absolute time. */
	abstime.tv_sec = -1;
	abstime.tv_nsec = 0;
	assert(pthread_cond_timedwait(&cond, &mtx, &abstime) == EINVAL);

	abstime.tv_sec = 0;
        abstime.tv_nsec = -1;
        assert(pthread_cond_timedwait(&cond, &mtx, &abstime) == EINVAL);

        assert(pthread_cond_timedwait(&cond, &mtx, NULL) == EINVAL);

	/* Timeout has passed. */
	abstime.tv_sec = 0;
	abstime.tv_nsec = 0;
	assert(pthread_cond_timedwait(&cond, &mtx, &abstime) == ETIMEDOUT);

	/* Release lock. */
	assert(pthread_mutex_unlock(&mtx) == 0);

	/* Cleanup. */
	assert(pthread_cond_destroy(&cond) == 0);
	assert(pthread_mutex_destroy(&mtx) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
