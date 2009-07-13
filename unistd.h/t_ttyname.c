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
	assert(ttyname(fd) != NULL);
	close(fd);

	/* invalild tty */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(ttyname(fd) == NULL && errno == ENOTTY);
	assert(close(fd) != -1);

	/* invalid fd */
	fd = -1;
	assert(ttyname(fd) == NULL && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
