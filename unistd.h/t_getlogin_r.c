#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	long guessed, sz, rv;
	char *p;

	/* Get max login name. */
	sz = -1;
	guessed = 0;
#ifdef	_SC_LOGIN_NAME_MAX
	sz = sysconf(_SC_LOGIN_NAME_MAX);
	assert(sz != -1);	/* It can't be infinite. */
#endif

	/* If querying sysconf database didn't work, just guess. */
	if (sz == -1) {
		sz = 1024;
		guessed = 1;
	}

	/* Allocate memory for buffer (+1 for the \0). */
	p = malloc(sz + 1);
	assert(p != NULL);

	/* Get login name, but if we guessed account for a potential error. */
	/* XXX: Allow the rest of the optional errors ? */
	rv = getlogin_r(p, sizeof(p));
	assert(rv == 0
	    || errno == ENXIO
	    || (guessed == 1 && errno == ERANGE));

	printf("passed");

	/* Test against ERANGE error (optional). */
	if (getlogin_r(p, 1) != ERANGE)
		printf(" (ERANGE test skipped)");

	printf("\n");

	/* Free memory. */
	free(p);

	return (EXIT_SUCCESS);
}
