#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for pid_t */
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

        /* Try to mess around with the mother of all process. */
        assert(setpriority(PRIO_PROCESS, 1, /* nice */ 0) == -1
	    && errno == EPERM);

	/* Be bad and try to lower our nice value, without having privilege. */
	pid = getpid();

	assert(setpriority(PRIO_PROCESS, pid, /* nice */ -10) == -1
	    && errno == EACCES);

	printf("passed\n");

	return (EXIT_SUCCESS);
}