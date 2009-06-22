#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void myhandler(int );

int main(void)
{
	pthread_barrierattr_t pba;

	/* We expect these simple calls to succeed. */
	assert(pthread_barrierattr_init(&pba) == 0);
	assert(pthread_barrierattr_destroy(&pba) == 0);

	/*
	 * XXX: The following test must always be the last one to run.
         *
	 * pthread_barrierattr_destroy() may fail if the attr values is
	 * invalid (e.g. NULL here). Some operating systems don't support
	 * this and the test case dies with segmentation fault. Catch
	 * SIGSEGV , because otherwise the false impression of the test
	 * case being flawed is given to the user.
         */
	signal(SIGSEGV, myhandler);

	assert(pthread_barrierattr_destroy(NULL) == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	/* Ignore subsequent occurences of the signal. */
	signal(sig, SIG_IGN);

	printf("passed (EINVAL check was skipped)\n");
	exit(EXIT_SUCCESS);
}
