#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void)
{
	struct rusage usage;

	/* We expect the following calls to succeed. */
	assert(getrusage(RUSAGE_SELF, &usage)  == 0);
	assert(getrusage(RUSAGE_CHILDREN, &usage) == 0);

	/* Invalid who argument. */
	assert(getrusage(-112233, &usage) == -1 && errno == EINVAL);
	assert(getrusage( 112233, &usage) == -1 && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
