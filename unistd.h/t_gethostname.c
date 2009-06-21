#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *buf;
	long sz = 2048;

#ifdef _SC_HOST_NAME_MAX
	/*
	 * sysconf(3) may return -1 as a legitimate value for variables
	 * that have no limit. In this case it doesn't touch errno.
	 */
	errno = 0;
	sz = sysconf(_SC_HOST_NAME_MAX);
	assert(sz != -1 || errno == 0);
#endif

	buf = malloc(sz);
	assert(buf != NULL);

	assert(gethostname(buf, sz) != -1);

	free(buf);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
