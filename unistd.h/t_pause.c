#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int generated = 0;

/* Function prototypes */
static void myhandler(int );

int main(void)
{
	/* Install signal handler. */
	signal(SIGALRM, myhandler);

	/* Request a signal in ~1sec from now. */
	alarm(1);

	/*
	 * Suspend indefinitely.
	 * If pause(3) fails to suspend us, then the following assertion
	 * will be almost immediately evaluated. The alarm(3) won't have
	 * delivered the signal and `generated' will still equal 0.
	 */
	assert(pause() == -1 && errno == EINTR);
	assert(generated == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	generated = 1;
}
