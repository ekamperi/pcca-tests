#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* for memset() */
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *buf;
	long sz = 32768;	/* Default value for PATH_MAX */

#ifdef _PC_PATH_MAX
	/* Determine maximum path length. */
	sz = pathconf(".", _PC_PATH_MAX);
	assert(sz != -1);	/* We surely don't allow infinite size
				   path names. */
#endif
	buf = malloc(sz);
	assert(buf != NULL);
	memset(buf, 0xff, sz);	/* Make sure we don't terminate prematurely. */

	assert(chdir(buf) == -1 && errno == ENAMETOOLONG);

	free(buf);

	/* Search permission is denied for any component of the pathname. */
	assert(chdir("sandbox/dir666/whatever") == -1 && errno == EACCES);

	/*
	 * A loop exists in symbolic links encountered during resolution of the
	 * path argument.
	 */
	assert(chdir("sandbox/loop") == -1 && errno == ELOOP);

	/* Path doesn't name an existing directory or is an empty string. */
	assert(chdir("/thisdefinitelydoesntexist") == -1 && errno == ENOENT);
	assert(chdir("") == -1 && errno == ENOENT);

	/* A path's component is not a directory. */
	assert(chdir("sandbox/notadir") == -1 && errno == ENOTDIR);

	/* We expect this simple call to succeed. */
	assert(chdir(".") == 0);

	/* XXX: This must be the last condition to be checked. */
	assert(chdir("..") == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
