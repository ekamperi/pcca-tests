#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd;

	/* Search permission is denied for the directory referenced by fd. */
	fd = open("sandbox/dir666", O_RDONLY);
	assert(fd != -1);
	assert(fchdir(fd) == -1 && errno == EACCES);
	assert(close(fd) != -1);

	/* Invalid (not open) file descriptor. */
	assert(fchdir(-1) == -1 && errno == EBADF);

	/* Open file descriptor, but not pointing to a directory. */
	fd = open("sandbox/file777", O_RDONLY);
	assert(fd != -1);
	assert(fchdir(fd) == -1 && errno == ENOTDIR);
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
