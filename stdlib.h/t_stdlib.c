#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

	/* EXIT_FAILURE evaluates to a non-zero value. */
#ifdef EXIT_FAILURE
	assert(EXIT_FAILURE != 0);
#endif

	/* EXIT_SUCCESS evaluates to 0. */
#ifdef EXIT_SUCCESS
	assert(EXIT_SUCCESS == 0);
#endif

	/* RAND_MAX should be at least 32767. */
#ifdef RAND_MAX
	assert(RAND_MAX >= 32767);
#endif

	/* The following data types need to be defined. */
	div_t x;
	ldiv_t y;
	lldiv_t z;
	size_t w;
	wchar_t t;

	printf("passed\n");

	return (EXIT_SUCCESS);
}
