#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
	struct rlimit rlm;

	/* Invalid resource parameter specified. */
	assert(getrlimit(-112233, &rlm) == -1 && errno == EINVAL);
	assert(getrlimit( 112233, &rlm) == -1 && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
