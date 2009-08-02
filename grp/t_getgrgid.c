#include <assert.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	struct group *gr, *res;
	gid_t gid;

	/* Get the real group ID of the calling process. */
	gid = getgid();

	/* Search the group database for an entry with a matching `gid'. */
	gr = getgrgid(gid);
	assert(gr != NULL);

	/*
	 * Test the thread safe version of it.
	 * XXX: Perhaps better use many threads ?
	 **/

	/*
	 * We need to determine the maximum size of the buffer needed by
	 * getgrgid_r(). If we can't query its value via sysconf(), we make
	 * a guess and use some adequately large for the common case, value.
	 */
	long rv = 65536;
#ifdef _SC_GETGR_R_SIZE_MAX
	rv = sysconf(_SC_GETGR_R_SIZE_MAX);
	assert(rv != -1);	/* We don't allow for indefinite values,
				   rv == -1 && errno == unchanged. */
#endif
	char *buf = malloc(rv);
	assert(buf != NULL);

	assert(getgrgid_r(gid, gr, buf, rv, &res) == 0);

	/*
	 * Just a sanity check; res shouldn't be NULL if the call was
	 * successful and we had a match.
	 */
	assert(res != NULL);

	/* Iterate over all members of our group. */
	while(*gr->gr_mem) {
		/*printf("-> %s\n", *gr->gr_mem);*/
		gr->gr_mem++;
	}

	/* Free buffer. */
	free(buf);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
