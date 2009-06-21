#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int generated = 0;

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	/* Install signal handler. */
	signal(SIGALRM, myhandler);

	/* Request an alarm just to cancel it right afterwards. */
	assert(alarm(1) == 0);
	assert(alarm(0) != 0);

	/* Just a sanity check */
	sleep(2);
	assert(generated == 0);

	/*
	 * After (roughly) 1 sec, a SIGALRM signal shall be generated
	 * and delivered to us.
	 */
	assert(alarm(1) == 0);
	sleep(2);
	assert(generated == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	generated = 1;
}
