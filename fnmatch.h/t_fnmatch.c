#include <assert.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
 
int main(void)
{
	int rv;

	rv = fnmatch(/* pattern */ "\\", "\\", 0);
	assert(rv == FNM_NOMATCH);

	rv = fnmatch(/* pattern */ "\\", "\\", FNM_NOESCAPE);
	assert(rv == 0);



	rv = fnmatch( /* pattern */ "p*", "path/to/file", 0);
	assert(rv == 0);

	rv = fnmatch("p*/*/*", "path/to/file", FNM_PATHNAME);
	assert(rv == 0);

	rv = fnmatch( /* patthern */ "p*", "path/to/file", FNM_PATHNAME);
	assert(rv == FNM_NOMATCH);



	rv = fnmatch( /* pattern */ "*", ".hidden", 0);
	assert(rv == 0);

	rv = fnmatch( /* pattern */ "*", ".hidden", FNM_PERIOD);
	assert(rv == FNM_NOMATCH);



	rv = fnmatch( /* pattern */ "*", "./file", 0);
	assert(rv == 0);

	rv = fnmatch( /* pattern */ "./*", "./file", FNM_PATHNAME | FNM_PERIOD);
	assert(rv == 0);

	rv = fnmatch( /* pattern */ "*", "./file", FNM_PATHNAME);
	assert(rv == FNM_NOMATCH);

	rv = fnmatch( /* pattern */ ".*", "./file", FNM_PATHNAME);
	assert(rv == FNM_NOMATCH);

	rv = fnmatch( /* pattern */ "*/*", "./file", FNM_PATHNAME | FNM_PERIOD);
	assert(rv == FNM_NOMATCH);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
