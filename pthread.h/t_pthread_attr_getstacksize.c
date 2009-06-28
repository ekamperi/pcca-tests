#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for PTHREAD_STACK_MIN */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	size_t stacksize;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Get size of stack size. */
	assert(pthread_attr_getstacksize(&attr, &stacksize) == 0);

	/* Set size of stack size. */
	assert(pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN-1) == EINVAL);

	assert(pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN+1) == 0);
	assert(pthread_attr_getstacksize(&attr, &stacksize) == 0);
	assert(stacksize == PTHREAD_STACK_MIN+1);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
