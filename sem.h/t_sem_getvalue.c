#include <assert.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	sem_t mysem;
	int val = 0;

	/* Create a semaphore. */
	assert(sem_init(&mysem,
		   0 /* not shared between processes */,
		   101 /* semaphore value */) == 0);

	/*
	 * Get the value of the semaphore.
	 * We assume that nothing has changed the value of our
	 * semaphore in the meantime.
	 */
	assert(sem_getvalue(&mysem, &val) == 0);
	assert(val == 101);

	/* Destroy previous. */
	assert(sem_destroy(&mysem) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
