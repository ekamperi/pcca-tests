#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;

	/* Valid tty. */
	/* XXX: Should we allocate a pty or can we safely rely on /dev/tty ? */
	fd = open("/dev/tty", O_RDONLY);
	assert(fd != -1);
	assert(isatty(fd) == 1);
	assert(close(fd) != -1);

	/* Invalid tty. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(isatty(fd) == 0 && errno == ENOTTY);
	assert(close(fd) != -1);

	/* Invalid fd. */
	fd = -1;
	assert(isatty(fd) == 0 && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
