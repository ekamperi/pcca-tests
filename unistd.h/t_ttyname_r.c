#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syslimits.h>

/*
 * ttyname_r(3) provides a different prototype than IEEE Std 1003.1-2001.
 * Check only errno variale values.
 */

int main(int argc, char *argv[])
{
	char big[PATH_MAX];
	char tiny[] = "/dev/ ";
	int fd;

	/* valid tty -- big buffer */
	fd = open("/dev/ttyp0", O_RDONLY);
	assert(fd >= 0);
	assert(ttyname_r(fd, big, sizeof(big)-1) != NULL);
	close(fd);

	/* valid tty -- tiny buffer */
	fd = open("/dev/ttyp0", O_RDONLY);
	assert(fd >= 0);
	assert(ttyname_r(fd, tiny, sizeof(tiny)-1) == NULL && errno == ERANGE);
	close(fd);

	/* bad file descriptor */
	fd = -1;
	assert(ttyname_r(fd, big, sizeof(big)-1) == NULL && errno == EBADF);

	/* invalid tty */
	fd = open(argv[0], O_RDONLY);
	assert(fd >= 0);
	assert(ttyname_r(fd, big, sizeof(big)-1) == NULL && errno == ENOTTY);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
