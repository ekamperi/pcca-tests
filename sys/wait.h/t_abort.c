#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(void)
{
	pid_t pid;

	/* Fork! */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/*
		 * We are inside the child.
		 *
		 * We are going to call abort() and the SIGABRT signal will be
		 * delivered to us (to the child only).
		 */
		abort();
	} else {
		/*
		 * We are inside the parent.
		 *
		 * We want to explore whether we can determine the exit status
		 * of the aborted child.
		 */

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/* Make sure the child exited due to a signal. */
		assert(WIFSIGNALED(status) != 0);

		/* ... and that the signal was SIGABRT. */
		assert(WTERMSIG(status) == SIGABRT);

		printf("passed\n");

		return (EXIT_SUCCESS);
	}
}
