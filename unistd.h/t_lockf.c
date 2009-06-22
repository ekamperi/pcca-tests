#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	FILENAME	"DONTDELETETHIS"

int main(void)
{
	int fd, function;

	/* Invalid file descriptor. */
	assert(lockf(-1, F_TLOCK, 0) == -1 && errno == EBADF);

	/*
	 * Valid file descriptor, but F_LOCK or F_TLOCK is supplied,
	 * and fd is not open for writing.
	 */
	fd = open(FILENAME, O_RDONLY);
	assert(fd != -1);

	assert(lockf(fd, F_LOCK, 0) == -1 && errno == EBADF);
	assert(lockf(fd, F_TLOCK, 0) == -1 && errno == EBADF);

	assert(close(fd) != -1);

	/* Invalid `function' requested. */
	function = 0;
#ifdef	F_LOCK
	function += F_LOCK;
#endif
#ifdef	F_TLOCK
	function += F_TLOCK;
#endif
#ifdef	F_TEST
	function += F_TEST;
#endif
#ifdef	F_ULOCK
	function += F_ULOCK;
#endif

	fd = open(FILENAME, O_RDWR);
	assert(fd != -1);
	assert(lockf(fd, function, 0) == -1 && errno == EINVAL);

	/* Size plus current file offset is less than 0. */
	assert(lseek(fd, 0, SEEK_SET) != -1);	/* Just a sanity check. */
	assert(lockf(fd, F_TLOCK, -1) == -1 && errno == EINVAL);

	assert(close(fd) != -1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
