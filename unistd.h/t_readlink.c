#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buf[4096];

	/* We are not a symbolic link. */
	assert(readlink(argv[0], buf, sizeof(buf) - 1) == -1 && errno == EINVAL);

	/* Provide invalid path to link. */
	assert(readlink("", buf, sizeof(buf) - 1) == -1 && errno == ENOENT);
	assert(readlink("/this/really/shouldn/t/exist",
			buf, sizeof(buf) - 1 == -1 && errno == ENOENT));

	/* XXX: Exceed maximum path length. */
	char *p;
	p = malloc(32768);
	assert(p != NULL);
	memset(p, 0xff, 32768);	/* Make sure we don't terminate prematurely. */
	assert(readlink(p, buf, sizeof(buf) - 1 == -1 && errno == ENAMETOOLONG));
	free(p);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
