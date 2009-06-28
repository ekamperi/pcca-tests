#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	struct sched_param param, param2;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract schedparam value from attribute object. */
	assert(pthread_attr_getschedparam(&attr, &param) == 0);

	/* Set schedparam. */
	param.sched_priority = 2;
	assert(pthread_attr_setschedparam(&attr, &param) == 0);
	assert(pthread_attr_getschedparam(&attr, &param2) == 0);
	assert(param2.sched_priority == 2);

	/*
	 * XXX: If _POSIX_SPORADIC_SERVER or _POSIX_THREAD_SPORADIC_SERVER
	 * symbols are defined, the sched_param structure is augmented with
	 * some additional members.
	 */

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
