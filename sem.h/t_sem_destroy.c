#include <assert.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	sem_t mysem;

	/* Create a semaphore. */
	assert(sem_init(&mysem,
		   0 /* not shared between processes */,
		   0 /* semaphore value */) == 0);

	/* Destroy previous. */
	assert(sem_destroy(&mysem) == 0);

	/* Semaphore argument doesn't represent a valid semaphore. */
	assert(sem_destroy(NULL) == -1 && errno == EINVAL);

	/*
	 * XXX: We don't support shared semaphores across processes, so
	 * we can't check against EBUSY.
	 */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
