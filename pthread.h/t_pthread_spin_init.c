#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pthread_spinlock_t lock;

	/* Initialize spinlock. */
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

	/* Destroy spinlock. */
	pthread_spin_destroy(&lock);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
