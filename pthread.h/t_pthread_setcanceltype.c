#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t th;
	int oldtype;

	/* Create new thread. */
	assert(pthread_create(&th, NULL, thread, (void *)NULL) == 0);

	/* Wait for thread to complete. */
	assert(pthread_join(th, NULL) == 0);

	/*
	 * The cancelability type of newly created threads, _including_ the
	 * thread in which main() was first invoked, is PTHREAD_CANCEL_DEFERRED.
	 */
	assert(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype)
	       == 0);
	assert(oldtype == PTHREAD_CANCEL_DEFERRED);

	/* XXX: This is optional. */
	assert(pthread_setcanceltype(-INT_MAX, &oldtype) == EINVAL);
	assert(oldtype == PTHREAD_CANCEL_ASYNCHRONOUS);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	int oldtype;

	assert(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype) == 0);
	assert(oldtype == PTHREAD_CANCEL_DEFERRED);

	pthread_exit(NULL);
}
