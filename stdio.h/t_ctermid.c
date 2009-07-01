#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char buf[L_ctermid];
	char *p;

	/* Zero out buffer. */
	memset(buf, 0, L_ctermid);

	/* The returned string must not be empty. */
	assert(strcmp(ctermid(buf), "") != 0);

	/* The result is in static area. */
	p = ctermid(NULL);
	assert(p != NULL && *p != '\0');

	/* Make sure the two calls, return the same string. */
	assert(strcmp(buf, p) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
