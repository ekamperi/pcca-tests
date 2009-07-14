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
	assert(rv == -1 && errno == EEXIST);

#ifdef NOTYET
	/*
	 * A loop exists in symbolic links encountered during resolution
	 * of the path1 or path2 argument.
	 */
	rv = link("sandbox/infloop", "sandbox/whatever");
	assert(rv == -1 && errno == ELOOP);

	rv = link("sandbox/file777", "sandbox/infloop");
	assert(rv == -1 && errno == ELOOP);
#endif

	/* XXX: Add test for ENAMETOOLONG. */

	/* A component of either path prefix is not a directory. */
	rv = link("sandbox/notadir/whatever", "sandbox/whatever");
	assert(rv == -1 && errno == ENOTDIR);

	rv = link("sandbox/file777", "sandbox/notadir/whatever");
	assert(rv == -1 && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
