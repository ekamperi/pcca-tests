#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int sigraised = 0;	/* Whether a SIGUSR1 signal was raised. */

/* Function prototypes. */
static void myhandler(int);

int main(void)
{
	/* Install signal handler. */
	struct sigaction sa;

	sa.sa_handler = myhandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	assert(sigaction(SIGUSR1, &sa, NULL) != -1);

	/* Fork! */
	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */

		/*
		 * Signal handlers are supposed to be inherited by parent/child
		 * across fork() calls. Verify it.
		 */
		struct sigaction oldsa;

		assert(sigaction(SIGUSR1, &sa, &oldsa) != -1);
		assert(oldsa.sa_handler == sa.sa_handler);
		assert(oldsa.sa_flags == sa.sa_flags);

		/*
		 * Raise the signal and make sure the signal was actually raised.
		 *
		 * Parent and child have a distinct copy of the `sigraised'
		 * global variable. So, changes done by parent don't affect
		 * child and vice versa.
		 */
		assert(raise(SIGUSR1) != -1);
		assert(sigraised == 1);
	} else {
		/* We are inside the parent. */

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/*
		 * XXX: Is it possible that wait() returns and a signal handler
		 * from the child is still running asynchronously ?
		 */

		/*
		 * Determine if the child exited normally, or due to a SIGABRT
		 * signal being delivered to it by a failed assertion.
		 */
		if (WIFSIGNALED(status)) {
			assert(WTERMSIG(status) == SIGABRT);
			return (EXIT_FAILURE);
		}

		/*
		 * Just as before verify that the signal handler before fork()
		 * is still in effect.
		 */
		struct sigaction oldsa;

		assert(sigaction(SIGUSR1, &sa, &oldsa) != -1);
		assert(oldsa.sa_handler == sa.sa_handler);
		assert(oldsa.sa_flags == sa.sa_flags);

		/* And raise the signal. */
		assert(raise(SIGUSR1) != -1);
		assert(sigraised == 1);

		printf("passed\n");

		return (EXIT_SUCCESS);
	}

	/* Only reached by child upon success. */
	return (EXIT_SUCCESS);
}

static void
myhandler(int signum)
{
	/* We don't expect any other signal beyond SIGUSR1. */
	assert(signum == SIGUSR1);

	sigraised++;
}
