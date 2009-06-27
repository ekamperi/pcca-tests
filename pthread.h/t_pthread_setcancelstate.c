#include <assert.h>
#include <errno.h>
#include <limits.h>	/* INT_MAX */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t th;
	int oldstate;

	/* Create new thread. */
	assert(pthread_create(&th, NULL, thread, (void *)NULL) == 0);

	/* Wait for thread to complete. */
	assert(pthread_join(th, NULL) == 0);

	/*
	 * The cancelability state of newly created threads, _including_ the
	 * thread in which main() was first invoked, is PTHREAD_CANCEL_ENABLE.
	 */
	assert(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate) == 0);
	assert(oldstate == PTHREAD_CANCEL_ENABLE);

	/* XXX: This is optional. */
	assert(pthread_setcancelstate(-INT_MAX, &oldstate) == EINVAL);
	assert(oldstate == PTHREAD_CANCEL_DISABLE);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	int oldstate;

	assert(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate) == 0);
	assert(oldstate == PTHREAD_CANCEL_ENABLE);

	pthread_exit(NULL);
}
