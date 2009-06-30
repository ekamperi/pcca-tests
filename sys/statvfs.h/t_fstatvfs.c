#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statvfs.h>

int main(int argc, char *argv[])
{
	struct statvfs buf;
	int fd, rv;

	/* Open file to obtain a file descriptor on it. */
	fd = open(argv[0], O_RDONLY);
	assert(fd != -1);

	/* Obtain file system information. */
	rv = statvfs(argv[0], &buf);
	assert(rv == 0);

	/* Close file. */
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
