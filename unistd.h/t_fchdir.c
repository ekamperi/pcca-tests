#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

	/* Invalid (not open) file descriptor. */
	assert(fchdir(-1) == -1 && errno == EBADF);

	/* Open file descriptor, but not pointing to a directory. */
	assert(fchdir(STDOUT_FILENO) == -1 && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
