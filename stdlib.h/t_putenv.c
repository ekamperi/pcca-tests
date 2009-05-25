#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	assert(putenv("foo") < 0);
	assert(putenv("=") < 0);
	assert(putenv("=123") < 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
