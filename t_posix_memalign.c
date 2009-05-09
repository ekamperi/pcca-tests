#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	void *ptr;
	int old_errno;

	/*
	 * save old errno value to see if posix_memalign() messes with it
	 * (error codes are supposed to be returned, not be saved to errno)
	 */
	old_errno = errno;

	/* alignment parameter is not a power of 2 */
	assert(posix_memalign(&ptr, 1 + (sizeof(void *) << 5), 100) == EINVAL);
	assert(old_errno == errno);

	/* alignment parameter is not at least as large as sizeof(void *) */
	assert(posix_memalign(&ptr, 0, 100) == EINVAL);
	assert(errno == old_errno);

	/* we expect this simple request to succeed */
	assert(posix_memalign(&ptr, sizeof(void *), 100) == 0);

	/* is it possible to realloc()/free() memory allocated via posix_memalign() ? */
	ptr = realloc(ptr, 200);
	assert(ptr != NULL);
	free(ptr);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
