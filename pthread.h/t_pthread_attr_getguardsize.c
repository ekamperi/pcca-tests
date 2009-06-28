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

	/* Invalid guard size. */
	assert(pthread_attr_getguardsize(&attr, NULL) == EINVAL);

	/* Get size of guard page. */
	assert(pthread_attr_getguardsize(&attr, &guardsize) == 0);

	/* Set size of guard page. */
	guardsize = 8000;
	assert(pthread_attr_setguardsize(&attr, &guardsize) == 0);
	assert(pthread_attr_getguardsize(&attr, &guardsize) == 0);
	/*
	 * We take into consideration the fact that the implementation
	 * may round guard size up to a multiple of page size.
	 */
	assert(guardsize >= 8000);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
