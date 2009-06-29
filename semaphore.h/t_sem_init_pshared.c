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
		   1 /* shared between processes */,
		   0 /* semaphore value */) == 0);

	/* Destroy previous. */
	assert(sem_destroy(&mysem) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
