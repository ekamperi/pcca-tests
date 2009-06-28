#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	size_t guardsize;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Get size of guard page. */
	assert(pthread_attr_getguardsize(&attr, &guardsize) == 0);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
