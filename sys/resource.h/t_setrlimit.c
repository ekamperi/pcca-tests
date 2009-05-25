#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <sys/resource.h>

int main(void)
{
	struct rlimit rlm;

	/* Invalid resource parameter specified. */
	assert(setrlimit(-112233, &rlm) == -1 && errno == EINVAL);
	assert(setrlimit( 112233, &rlm) == -1 && errno == EINVAL);

	/* Try increasing maximum limit value without being super-user. */
	/* Zero out structure. */
	memset(&rlm, 0, sizeof(struct rlimit));

	/* Get current stack size limit. */
	assert(getrlimit(RLIMIT_STACK, &rlm) == 0);

	/* Make sure we don't overflow. */
	if (rlm.rlim_max + 1 > rlm.rlim_max++)
		assert(setrlimit(RLIMIT_STACK, &rlm) == -1 && errno == EPERM);
	else
		fprintf(stderr, "Skipping check.\n");

	/*
	 * Supply invalid address for the rlimit structure.
	 * This is DragonFly specific.
	 */
#ifdef __DragonFly__
	assert(setrlimit(RLIMIT_STACK, 0) == -1 && errno == EFAULT);
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
