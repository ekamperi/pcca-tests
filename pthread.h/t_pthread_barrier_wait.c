
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int rv_pbst = 0;	/* Whether PTHREAD_BARRIER_SERIAL_THREAD was returned.*/
int rv_zero = 0;	/* Whether zero was returned. */

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_barrier_t pb;
	pthread_t th1, th2;

	/* Initialize barrier. */
	assert(pthread_barrier_init(&pb, NULL, 2) == 0);

	/* Create threads. */
	assert(pthread_create(&th1, NULL, thread, (void *)&pb) == 0);
	assert(pthread_create(&th2, NULL, thread, (void *)&pb) == 0);

	/* Wait for threads to complete. */
	assert(pthread_join(th1, NULL) == 0);
	assert(pthread_join(th2, NULL) == 0);

	/* Destroy barrier. */
	assert(pthread_barrier_destroy(&pb) == 0);

	/*
	 * PTHREAD_BARRIER_SERIAL_THREAD should be returned to one thread and
	 * zero to the other (but we don't know which one gets what).
	 */
	assert(rv_pbst == 1 && rv_zero == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	pthread_barrier_t *pb;
	int rv;

	/*
	 * Retrieve reference to the original barrier.
	 *
	 * Don't be tempted to dereference `arg' and get a copy of the barrier.
	 * The result of calling pthread_barrier_wait() on the copy will be
	 * undefined.
	 */
	pb = (pthread_barrier_t *)arg;

	/* This will block us. */
	rv = pthread_barrier_wait(pb);
	if (rv == PTHREAD_BARRIER_SERIAL_THREAD)
		rv_pbst = 1;
	else if (rv == 0)
		rv_zero = 1;

	pthread_exit(NULL);
}
