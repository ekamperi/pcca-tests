#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	int rv;

	/* A component of path prefix denies search permission. */
	rv = link("sandbox/dir666/whatever", "sandbox/whatever");
	assert(rv == -1 && errno == EACCES);

	/*
	 * The requested link requires writing in a directory that denies
	 * write permission.
	 */
	rv = link("sandbox/file777", "sandbox/dir555/whatever");
	assert(rv == -1 && errno == EACCES);

	/* The `path2' argument resolves to an existing file. */
	rv = link("sandbox/file777", "sandbox/file777");
	assert(rv == -1 && errno == EEXIST);

	/* The `path2' argument' refers to a symbolic link. */
	rv = link("sandbox/file777", "sandbox/fileloop");

	printf("passed\n");

	return (EXIT_SUCCESS);
}
