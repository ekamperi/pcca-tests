#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	uid_t uid;

	/* Get real user ID of the calling process. */
	uid = getuid();

	printf("passed\n");

	return (EXIT_SUCCESS);
}
