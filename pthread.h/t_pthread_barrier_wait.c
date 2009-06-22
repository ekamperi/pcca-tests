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

	/* Create the threads. */
	assert(pthread_create(&th1, NULL, thread, (void *)&pb) == 0);
	assert(pthread_create(&th2, NULL, thread, (void *)&pb) == 0);

	/* Wait for threads to complete. */
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	/* Destroy barrier. */
	assert(pthread_barrier_destroy(&pb) == 0);

	assert(rv_pbst == 1 && rv_zero == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	pthread_barrier_t pb;
	int rv;

	/* Retrieve barrier. */
	pb = *(pthread_barrier_t *)arg;

	/* This will block us. */
	rv = pthread_barrier_wait(&pb);
	if (rv == PTHREAD_BARRIER_SERIAL_THREAD)
		rv_pbst = 1;
	else if (rv == 0)
		rv_zero = 1;

	pthread_exit(NULL);
}
