#include <assert.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
 
int main(void)
{
	DIR *dirp;
	struct dirent *dp;
	const char *pattern;
	int dot, dotdot, rv;

	/* Open directory stream. */
	dirp = opendir(".");
	assert(dirp != NULL);


	/* Scan directory and match . and .. */
	dot = 0;
	dotdot = 0;
	while ((dp = readdir(dirp)) != NULL) {
		/* First */
		pattern = ".";
		rv = fnmatch(pattern, dp->d_name, 0);
		if (rv == 0) {
			dot++;
		} else {
			/* It either matches, or not. The rest are errors. */
			assert(rv == FNM_NOMATCH);
		}

		/* Second */
		pattern = "..";
		rv = fnmatch(pattern, dp->d_name, 0);
		if (rv == 0) {
			dotdot++;
		} else {
			/* It either matches, or not. The rest are errors. */
			assert(rv == FNM_NOMATCH);
		}
	}

	/* Close directory stream. */
	assert(closedir(dirp) == 0);

	/* Make sure we match _exactly one_ for both of them. */
	assert(dot == 1 && dotdot == 1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
