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

#ifdef SEM_VALUE_MAX
	/*
	 * Try to exceed maximum allowed value for semaphore, but first make
	 * sure we don't overflow. Otherwise, the value will most likely truncate
	 * to 0 and spurious results will be produced.
	 */
	if (SEM_VALUE_MAX + 1 > SEM_VALUE_MAX) {
		assert(sem_init(&mysem,
			   0 /* not shared between processes */,
			   SEM_VALUE_MAX + 1) == -1 && errno == EINVAL);
	}
#endif

	printf("passed\n");

	return (EXIT_SUCCESS);
}
