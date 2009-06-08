#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	BUFSIZE	1024

int main(void)
{
	char buf[BUFSIZE + 1];	/* Reserve space for '\0' */

	/* Zero out buffer. */
	memset(buf, 0, BUFSIZE + 1);

	/*
	 * POSIX allows basename() to modify the string pointed to by path.
	 * Therefore, avoid passing string literals, as they are non-writeable.
	 */
	strncpy(buf, "/usr/lib", BUFSIZE);
	assert(strcmp(basename(buf), "lib") == 0);

	strncpy(buf, "/usr/", BUFSIZE);
	assert(strcmp(basename(buf), "usr") == 0);

	strncpy(buf, "/", BUFSIZE);
        assert(strcmp(basename(buf), "/") == 0);

	strncpy(buf, "///", BUFSIZE);
        assert(strcmp(basename(buf), "/") == 0);

	strncpy(buf, "//usr//lib//", BUFSIZE);
        assert(strcmp(basename(buf), "lib") == 0);

	strncpy(buf, "", BUFSIZE);
	assert(strcmp(basename(buf), ".") == 0);

	assert(strcmp(basename(NULL), ".") == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
