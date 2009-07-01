#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	struct termios oldt;
	int fd;

	/* Make sure we are associated with a tty. */
	assert(isatty(STDIN_FILENO) != 0);

	/* Get current termios structure. */
	assert(tcgetattr(STDIN_FILENO, &oldt) != -1);

	/* Bad file descriptor. */
	assert(tcgetattr(-1, &oldt) == -1 && errno == EBADF);

	/* File descriptor is not associated with a terminal. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(tcgetattr(fd, &oldt) == -1 && errno == ENOTTY);
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
