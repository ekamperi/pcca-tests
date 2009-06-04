#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

int main(int argc, char *argv[])
{
	char *p;
	size_t sz = 4096;	/* Default value for PATH_MAX */

	/* Mess with /root. */
	assert(opendir("/root") == NULL && errno == EACCES);

	/* Exceed maximum path length limit. */
#ifdef	_PC_PATH_MAX
	/* Determine maximum path length. */
	sz = pathconf(".", "_PC_PATH_MAX");
	assert(sz != -1);
#endif
	p = malloc(sz + 1);
	assert(p != NULL);
	memset(p, 0xff, sz + 1);	/* Make sure we don't terminate early.*/
	assert(opendir(p) == NULL && errno == ENAMETOOLONG);
	free(p);

	/* Directory doesn't exist. */
	assert(opendir("/this/certainly/shouldn/t/exist") == NULL && errno == ENOENT);

	/* Try to open something that isn't a dir. */
	assert(opendir(argv[0]) == NULL && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
