#define _XOPEN_SOURCE 600

#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	/* Get process group ID of the current process (both ways). */
	assert(getpgid(0) == getpgid(getpid()));

	/* EINVAL is optional, but we must allow it as it may precede ESRCH. */
	assert(getpgid(-INT_MAX) == (pid_t)-1
	    && (errno == ESRCH || errno == EINVAL));

	/* Fork and let child create a new session. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */

		/* Allow the child to create a new session. */
		sleep(1);

		/*
		 * Try to get the process group ID from a process belonging to
		 * another session. This may optionally fail with EPERM.
		 */
		if (getpgid(pid) == (pid_t)-1) {
			assert(errno == EPERM);
			printf("passed\n");
		}
		else
			printf("passed (EPERM check skipped)\n");

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);
	} else {
		/* We are inside the child. */

		/* Create a new session. */
		assert(setsid() != (pid_t)-1);

		/* And then sleep for a while, so that parent can probe us. */
		sleep(2);
	}

	return (EXIT_SUCCESS);
}
