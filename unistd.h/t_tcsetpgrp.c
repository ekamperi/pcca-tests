#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t oldpgid, pid;
	int fd, rv, status;

	/* Bad file descriptor. */
	assert(tcsetpgrp(-1, getpgid(0)) == -1 && errno == EBADF);

	/* Invalid process group id. */
	assert(tcsetpgrp(STDIN_FILENO, -INT_MAX) ==  -1 && errno == EINVAL);

	/* Not a controlling terminal. */
	fd = open("sandbox/notatty", O_RDONLY);
	assert(fd != -1);
	assert(tcsetpgrp(fd, getpgid(0)) == -1 && errno == ENOTTY);
	assert(close(fd) != -1);

	/* Fork! */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		assert(wait(&status) == pid);

		printf("passed\n");
	} else {
		/* We are inside the child. */

		/*
		 * The child process ID doesn't match any active process
		 * group ID. So the following call should fail with EPERM.
		 *
		 * XXX: In Linux this call "succeeds" (i.e. it returns 0),
		 * but the process group id doesn't change at all!
		 */
		assert(tcsetpgrp(STDIN_FILENO, getpid()) == -1
		    && errno == EPERM);
	}
	
	return (EXIT_SUCCESS);
}
