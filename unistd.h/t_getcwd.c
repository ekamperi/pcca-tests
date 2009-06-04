#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* strlen() */
#include <unistd.h>

int main(void)
{
	char *buf;
	size_t sz = 4096;	/* Default value for PATH_MAX */

#ifdef _PC_PATH_MAX
	/* Determine maximum path length. */
	sz = pathconf(".", _PC_PATH_MAX);
#endif
	buf = malloc(sz);
	assert(buf != NULL);

        /* We expect this simple call to succeed. */
        assert(getcwd(buf, sz - 1) != NULL);

	/* The size argument is 0. */
	assert(getcwd(buf, 0) == NULL && errno == EINVAL);

	/* The size is too small (but greater than 0) to hold pathname + 1. */
	assert(getcwd(buf, 1) == NULL && errno == ERANGE);

	free(buf);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
