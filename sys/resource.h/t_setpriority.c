#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
	pid_t pid;

	/* Invalid `which' value. */
	assert(setpriority(-112233, 1, /* nice */ 0) == -1 && errno == EINVAL);
	assert(setpriority( 112233, 1, /* nice */ 0) == -1 && errno == EINVAL);

	/* Valid `which' value, but no process with `which,who' pair found. */
	assert(setpriority(PRIO_USER, -1, /* nice */ 0) == -1
	    && errno == ESRCH);

	/* Be bad and try to lower our nice value, without having privilege. */
	pid = getpid();

	errno = 0;
	assert(setpriority(PRIO_PROCESS, pid, /* nice */ -10) == -1
	    && errno == EACCES);

	/*
	 * POSIX says that we couldn't _change_ (thus not even increase)
	 * our nice value.
	 */
	errno = 0;
	assert(setpriority(PRIO_PROCESS, pid, /* nice */ 10) == -1
            && errno == EACCES);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
