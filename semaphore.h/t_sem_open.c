#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>	/* for SEM_VALUE_MAX */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SEMNAME	"/tso"

int main(void)
{
	sem_t *mysem;
	sem_t *mysem2;

	/* Create named semaphore. */
	mysem = sem_open(SEMNAME, O_CREAT | O_EXCL,
			 0777	/* Access mode */,
			 1	/* Initial value */);
	assert(mysem != SEM_FAILED);

	/*
	 * If a process makes multiple successful calls to sem_open() with the
	 * same value for name, the same semaphore address will be returned.
	 */
	mysem2 = sem_open(SEMNAME, O_CREAT);
	assert(mysem2 != SEM_FAILED);
	assert(mysem2 == mysem);

	/* XXX: How do we check against EACCESS ? */

	/* O_CREAT and O_EXCL are set and the named semaphore already exists. */
	assert(sem_open(SEMNAME, O_CREAT | O_EXCL) == SEM_FAILED
	    && errno == EEXIST);

	/* Invalid name. */
	assert(sem_open("", O_CREAT | O_EXCL) == SEM_FAILED && errno == EINVAL);

#ifdef SEM_VALUE_MAX
        /*
         * Try to exceed maximum allowed value for semaphore, but first make
         * sure we don't overflow. Otherwise, the value will most likely truncate
         * to 0 and spurious results will be produced.
         */
        if (SEM_VALUE_MAX + 1 > SEM_VALUE_MAX) {
		assert(sem_open(SEMNAME, O_CREAT) == SEM_FAILED
		    && errno == EINVAL);
	}
#endif

	/* O_CREAT is not set and the named semaphore does not exist. */
	assert(sem_open("/thisdefinitelydoesntexist", ~O_CREAT) == SEM_FAILED
	    && errno == ENOENT);

	/* Disassociate from semaphore. */
	assert(sem_close(mysem) == 0);
	assert(sem_close(mysem2) == 0);

	/* Remove semaphore from system. */
	assert(sem_unlink(SEMNAME) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
