#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;

	/* valid tty */
	fd = open("/dev/ttyp0", O_RDONLY);
	assert(fd >= 0);
	assert(isatty(fd) == 1);
	close(fd);

	/* invalid tty */
	fd = open(argv[0], O_RDONLY);
	assert(fd >= 0);
	assert(isatty(fd) == 0 && errno == ENOTTY);
	close(fd);

	/* invalid fd */
	fd = -1;
	assert(isatty(fd) == 0 && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
