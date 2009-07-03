#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
	struct termios t;
	int fd;

	/* Make sure we are associated with a tty. */
	assert(isatty(STDIN_FILENO) != 0);

	/* Get current termios structure. */
	assert(tcgetattr(STDIN_FILENO, &t) != -1);

	/* ... and set it again! */
	assert(tcsetattr(STDIN_FILENO, TCSANOW, &t) != -1);

	/* Bad file descriptor. */
	assert(tcsetattr(-1, TCSANOW, &t) == -1 && errno == EBADF);

	/* Invalid optional actions arguments. */
#if 0
	/*
	 * "In general, an implementation must be conservative in its sending
	 * behavior, and liberal in its receiving behavior... where the meaning
	 * is still clear. But here it isn't. Anyway, since most mainstream OSes
	 * don't validate input, disable it for now.
	 * Source: http://www.ietf.org/rfc/rfc0791.txt
	 */
	assert(tcsetattr(STDIN_FILENO, TCSANOW | TCSADRAIN, &t) == -1
	       && errno == EINVAL);

	assert(tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &t) == -1
	       && errno == EINVAL);

	assert(tcsetattr(STDIN_FILENO, TCSADRAIN | TCSAFLUSH, &t) == -1
	       && errno == EINVAL);
#endif
	assert(tcsetattr(STDIN_FILENO, -INT_MAX, &t) == -1
	       && errno == EINVAL);

	/* File descriptor is not associated with a terminal. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(tcgetsid(fd) == (pid_t)-1 && errno == ENOTTY);
	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
