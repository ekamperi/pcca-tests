#include <assert.h>
#include <errno.h>
#include <limits.h>	/* INT_MAX */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	int inheritsched;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract inheritsched value from attribute object. */
	assert(pthread_attr_getinheritsched(&attr, &inheritsched) == 0);
	assert(inheritsched == PTHREAD_INHERIT_SCHED ||
	       inheritsched == PTHREAD_EXPLICIT_SCHED);

	/* Set inheritsched. */
	assert(pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED) == 0);
	inheritsched = -INT_MAX;	/* Paranoia. */
	assert(pthread_attr_getinheritsched(&attr, &inheritsched) == 0);
	assert(inheritsched == PTHREAD_INHERIT_SCHED);

        assert(pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) == 0);
        inheritsched = -INT_MAX;        /* Paranoia. */
        assert(pthread_attr_getinheritsched(&attr, &inheritsched) == 0);
        assert(inheritsched == PTHREAD_EXPLICIT_SCHED);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
