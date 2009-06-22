#include <assert.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	sem_t mysem;
	int val = 999;

	/* Create a semaphore. */
	assert(sem_init(&mysem,
		   0 /* not shared between processes */,
		   1 /* semaphore value */) == 0);

	/* Lock semaphore. */
	assert(sem_trywait(&mysem) == 0);

	/*
	 * Make sure the sem value has been lowered to zero or negative.
	 * A negative value represents the number of processes blocked by
	 * us.
	 */
	assert(sem_getvalue(&mysem, &val) == 0);
	assert(val < 0 || val == 0);

	/* This must fail with EAGAIN. */
	assert(sem_trywait(&mysem) == -1 && errno == EAGAIN);

	/* Unlock semaphore. */
	assert(sem_post(&mysem) == 0);

	/* We should be at exactly where we started. */
	assert(sem_getvalue(&mysem, &val) == 0);
	assert(val == 1);

	/* Destroy previous. */
	assert(sem_destroy(&mysem) == 0);

        /* XXX optional */
        assert(sem_trywait(NULL) == -1 && errno == EINVAL);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
