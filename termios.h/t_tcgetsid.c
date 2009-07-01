#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
	int fd;

	/* Make sure we are associated with a tty. */
	assert(isatty(STDIN_FILENO) != 0);

	/* We expect this simple call to succeed. */
	assert(tcgetsid(STDIN_FILENO) != (pid_t)-1);

	/* Bad file descriptor. */
        assert(tcgetsid(-1) == (pid_t)-1 && errno == EBADF);

        /* File descriptor is not associated with a terminal. */
        fd = open("sandbox/notatty", O_RDONLY);
        assert(fd != -1);
        assert(tcgetsid(fd) == (pid_t)-1 && errno == ENOTTY);
        assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
