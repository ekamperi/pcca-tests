#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for PTHREAD_STACK_MIN */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_attr_t attr;
	void *stackaddr;
	size_t stacksize;

	/* Initialize thread attribute object. */
	assert(pthread_attr_init(&attr) == 0);

	/* Extract stack properties from attribute object.  */
	assert(pthread_attr_getstack(&attr, &stackaddr, &stacksize) == 0);

	/* Make sure default properties are valid. */
	assert(stacksize >= PTHREAD_STACK_MIN);

	/*
	 * Set stack properties on attribute object.
	 * Some architectures may require that stack address is 8-byte
	 * aligned, so take care of it.
	 */
	assert(pthread_attr_setstack(&attr, (void *)0x08, stacksize) == 0);

	/* Destroy thread attribute object. */
	assert(pthread_attr_destroy(&attr) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
