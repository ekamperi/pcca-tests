#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DIR *dp;

	/* Bad directory stream. */
	assert(closedir(NULL) == 0 && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
