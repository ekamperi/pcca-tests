#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	/* Get process ID of the calling process. */
	pid = getpid();

	printf("passed\n");

	return (EXIT_SUCCESS);
}
