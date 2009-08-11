#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int rv;

	rv = access("sandbox/rootfile600", R_OK);
	assert(rv == -1 && errno == EACCES);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
