#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for pid_t */
#include <sys/resource.h>

int main(void)
{
	pid_t pid;
	int prio;

	/* We expect this simple operation to succeed. */
	pid = getpid();

	assert(setpriority(PRIO_PROCESS, pid, 2) == 0);

	/* getpriority() can return -1 on success, so zero out errno. */
	errno = 0;
	prio = getpriority(PRIO_PROCESS, pid);
	assert(prio != -1 || errno == 0);
	assert(prio == 2);

	/* Invalid `which' value. */
	assert(setpriority(-112233, 1, /* nice */ 0) == -1 && errno == EINVAL);
	assert(setpriority( 112233, 1, /* nice */ 0) == -1 && errno == EINVAL);

	/* Valid `which' value, but no process with `which,who' pair found. */
	assert(setpriority(PRIO_USER, -1, /* nice */ 0) == -1
	    && errno == ESRCH);

        /* Try to mess around with the mother of all process. */
        assert(setpriority(PRIO_PROCESS, 1, /* nice */ 0) == -1
	    && errno == EPERM);

#if 0
	/*
	 * Be bad and try to lower our nice value, without having privilege.
	 * POSIX only suggests in this matter, so we can't expect one behaviour.
	 * E.g, the OS may renice up to the minimum allowed nice value
	 * (DragonFly does).
	 */
	pid_t pid;
	pid = getpid();

	assert(setpriority(PRIO_PROCESS, pid, /* nice */ -10) == -1
	    && errno == EACCES);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
