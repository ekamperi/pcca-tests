#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pgid;

	/* Get the process group ID of the calling process. */
	pgid = getpgrp();

	/* Those two must match. */
	assert(pgid == getpgid(0));
	assert(pgid == getpgid(getpid()));

	printf("passed\n");

	return (EXIT_SUCCESS);
}
