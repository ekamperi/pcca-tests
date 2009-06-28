#include <assert.h>
#include <errno.h>
#include <limits.h>	/* INT_MAX */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	int contentionscope;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract contention scope value from attribute object. */
	assert(pthread_attr_getscope(&attr, &contentionscope) == 0);
	assert(contentionscope == PTHREAD_SCOPE_SYSTEM ||
	       contentionscope == PTHREAD_SCOPE_PROCESS);

	/* Set contention scope. */
	assert(pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) == 0);
	contentionscope = -INT_MAX;	/* Paranoia. */
	assert(pthread_attr_getscope(&attr, &contentionscope) == 0);
	assert(contentionscope == PTHREAD_SCOPE_SYSTEM);

	assert(pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS) == 0);
	contentionscope = -INT_MAX;     /* Paranoia. */
	assert(pthread_attr_getscope(&attr, &contentionscope) == 0);
	assert(contentionscope == PTHREAD_SCOPE_PROCESS);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
