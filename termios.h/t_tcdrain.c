#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/wait.h>

int issignaled = 0;

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	pid_t pgid, pid;

	/*
	 * Had we wanted to be more robust, we wouldn't rely on our program
	 * being invoked by a terminal. We would instead allocate a pty with
	 * open + ptsname + grantpt + unlockpt.
	 */
	assert(isatty(STDIN_FILENO) != 0);

	/* Fork! */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		/* Make us the foreground process group. */
		pgid = getpgid(0);
		assert(tcsetpgrp(STDIN_FILENO, pgid) == 0);

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		printf("passed\n");
	} else {
		/* We are inside the child. */
		/*
		 * Wait for parent to become foreground process group.
		 * XXX: Is it really needed ?
		 */
		sleep(1);

		/* Install signal handler. */
		signal(SIGTTOU, myhandler);

		/*
		 * Create a new process group. And since the old one is the
		 * foreground, that leaves us with being the background process
		 * group.
		 */
		pid = getpid();
		assert(setpgid(0, pid) == 0);

		/*
		 * This should raise SIGTTOU signal to us, because we try to
		 * write to the terminal while belonging to a background process
		 * group.
		 */
		assert(tcdrain(STDIN_FILENO) == 0);

		assert(issignaled == 1);
	}

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	signal(SIGTTOU, SIG_IGN);
	issignaled = 1;
}
