#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

int main(int argc, char *argv[])
{
	DIR *dp;
	char *p;

	/* Mess with /root. */
	assert(opendir("/root") == NULL && errno == EACCES);

	/* Overflow PATH_MAX constant. */
	p = malloc(2 * PATH_MAX);
	assert(p != NULL);
	memset(p, 0xff, 2 * PATH_MAX);	/* Make sure we don't terminate early.*/
	assert(opendir(p) == NULL & errno == ENAMETOOLONG);
	free(p);

	/* Directory doesn't exist. */
	assert(opendir("/this/certainly/shouldn/t/exist") == NULL && errno == ENOENT);

	/* Try to open something that isn't a dir. */
	assert(opendir(argv[0]) == NULL && errno == ENOTDIR);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
