#define _XOPEN_SOURCE 600

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int
main(void)
{
	/* Construct numbers with all theis bits 0 except a moving 1. */
	int i;

	for (i = 0; i < 20; i++)
		assert(ffs(1 << i) == (i + 1));

	/* Special case. */
	assert(ffs(0) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);;
}
