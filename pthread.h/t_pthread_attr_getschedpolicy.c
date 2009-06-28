#include <assert.h>
#include <errno.h>
#include <limits.h>	/* INT_MAX */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	int policy;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract policy value from attribute object. */
	assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
	assert(policy == SCHED_FIFO || policy == SCHED_RR ||
	       policy == SCHED_OTHER);

	/* Set policy. */
	/* SCHED_FIFO */
	assert(pthread_attr_setschedpolicy(&attr, SCHED_FIFO) == 0);
	policy = -INT_MAX;	/* Paranoia. */
	assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
	assert(policy == SCHED_FIFO);

	/* SCHED_RR */
        assert(pthread_attr_setschedpolicy(&attr, SCHED_RR) == 0);
        policy = -INT_MAX;      /* Paranoia. */
        assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
        assert(policy == SCHED_RR);

	/* SCHED_OTHER */
        assert(pthread_attr_setschedpolicy(&attr, SCHED_OTHER) == 0);
        policy = -INT_MAX;      /* Paranoia. */
        assert(pthread_attr_getschedpolicy(&attr, &policy) == 0);
        assert(policy == SCHED_OTHER);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
