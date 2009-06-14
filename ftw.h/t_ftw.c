#include <assert.h>
#include <errno.h>
#include <limits.h>	/* for OPEN_MAX */
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static int mycallback(const char *, const struct stat *, int);

int main(int argc, char *argv[])
{
	/* ndirs isn't in the range [1, {OPEN_MAX}] */
	assert(ftw(".", mycallback, 0) == -1 && errno == EINVAL);
#ifdef OPEN_MAX
	assert(ftw(".", mycallback, OPEN_MAX + 1) == -1 && errno == EINVAL);
#endif

	/* Inexistent path. */
	assert(ftw("", mycallback, 1) == -1 && errno == ENOENT);
	assert(ftw("/thisdefinitelydoesntexist", mycallback, 1) == -1 &&
	       errno == ENOENT);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static int
mycallback(const char *path, const struct stat *pstat, int flag)
{
	printf("%s\n", path);

	return 0;
}
