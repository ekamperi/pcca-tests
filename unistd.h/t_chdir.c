#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* for memset() */
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *buf;
	size_t sz = 32768;	/* Default value for PATH_MAX */

#ifdef _PC_PATH_MAX
	/* Determine maximum path length. */
	sz = pathconf(".", _PC_PATH_MAX);
#endif
	buf = malloc(sz);
	assert(buf != NULL);
	memset(buf, 0xff, sz);	/* Make sure we don't terminate prematurely. */

	assert(chdir(buf) == -1 && errno == ENAMETOOLONG);

	free(buf);

	/* Path doesn't name an existing directory or is an empty string. */
	assert(chdir("/thisdefinitelydoesntexist") == -1 && errno == ENOENT);
	assert(chdir("") == -1 && errno == ENOENT);

	/* A path's component is not a directory. */
	assert(chdir(argv[0]) == -1 && errno == ENOTDIR);

	/* We expect this simple call to succeed. */
	assert(chdir(".") == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
