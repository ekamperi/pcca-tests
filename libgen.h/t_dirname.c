#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main(void)
{
	char buf[BUFSIZE + 1];	/* Reserve space for '\0' */

	/* Zero out buffer. */
	memset(buf, 0, BUFSIZE + 1);

	/*
	 * POSIX says that dirname() may modify the supplied string.
	 * So, don't pass a literal string which by definition is
	 * not writeable.
	 */
	assert(strcmp(dirname(NULL), ".") == 0);

	strncpy(buf, "this doesnt contain slash", BUFSIZE);
	assert(strcmp(dirname(buf), ".") == 0);

	strncpy(buf, "/trailing/slashes//", BUFSIZE);
	assert(strcmp(dirname(buf), "/trailing") == 0);

	strncpy(buf, "/more//trailing//", BUFSIZE);
	assert(strcmp(dirname(buf), "/more") == 0);

	strncpy(buf, "missing/slash", BUFSIZE);
	assert(strcmp(dirname(buf), "missing") == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
