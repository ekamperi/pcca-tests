#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_spinlock_t lock;

	/* Initialize spinlock. */
	assert(pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Acquire spinlock. */
	assert(pthread_spin_lock(&lock) == 0);

	/* Release spinlock. */
	assert(pthread_spin_unlock(&lock) == 0);

	/* Destroy spinlock. */
	assert(pthread_spin_destroy(&lock) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
