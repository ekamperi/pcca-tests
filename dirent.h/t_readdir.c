#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *dp;
	int found;

	/* Open directory stream. */
	dirp = opendir(".");
	assert(dirp != NULL);

	/* Iterate through the stream and make sure that . and .. are found. */
	found = 0;
	while ((dp = readdir(dirp)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0)
			found++;
		if (strcmp(dp->d_name, "..") == 0)
			found++;
	}

	assert(found == 2);

	assert(closedir(dirp) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
