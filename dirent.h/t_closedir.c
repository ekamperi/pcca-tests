#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void myhandler(int );

int main(void)
{
	DIR *dirp;

	/* We expect this simple operation to succeed. */
	assert((dirp = opendir(".")) != NULL);
	assert(closedir(dirp) == 0);

	/*
	 * XXX: The following test must always be the last one to run.
	 *
	 * POSIX suggests that if the supplied argument of closedir(3) doesn't
	 * refer to an open directory stream, EBADF _may_ be returned. Some
	 * operating systems don't and the test case dies with segmentation
	 * fault. Catch SIGSEGV , because otherwise the false impression of
	 * the test case being flawed is given to the user.
	 */
	signal(SIGSEGV, myhandler);

	/* Bad directory stream. */
	assert(closedir(NULL) == 0 && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void
myhandler(int sig)
{
	/* Ignore subsequent occurences of the signal. */
	signal(sig, SIG_IGN);

	printf("passed (EBADF check was skipped)\n");
	exit(EXIT_SUCCESS);
}
