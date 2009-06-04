#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/* We expect our binary to exist, while we are running. */
	assert(access(argv[0], F_OK) == 0);

	/* Spy /root */
	assert(access("/root", R_OK | W_OK | X_OK | F_OK) == -1 &&
	       errno == EACCES);

	/* Probe non existent paths. */
	assert(access("", F_OK) == -1 && errno == ENOENT);
	assert(access("/this/really/shouln/t/exist", F_OK) == -1 &&
	       errno == ENOENT);

#if 0
	/* This is optional. */
	assert(access(argv[0], ~(R_OK | W_OK | X_OK | F_OK)) == -1 && errno == EINVAL);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
