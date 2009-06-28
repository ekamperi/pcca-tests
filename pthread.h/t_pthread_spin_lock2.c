#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for sleep(3) */

pthread_spinlock_t lock;

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t tid;

	/* Initialize spinlock. */
	assert(pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Create thread. */
	assert(pthread_create(&tid, NULL, thread, (void *)NULL) == 0);

	/* Sleep so that the thread acquires the spinlock. */
	sleep(1);

	/* Try to acquire lock while thread() still holds it. */
	assert(pthread_spin_trylock(&lock) == EBUSY);

	/* Acquire spinlock -- this will spin. */
	assert(pthread_spin_lock(&lock) == 0);

	/* Release spinlock. */
	assert(pthread_spin_unlock(&lock) == 0);

	/* Destroy spinlock. */
	assert(pthread_spin_destroy(&lock) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	/* Acquire spinlock. */
	assert(pthread_spin_lock(&lock) == 0);

	/*
	 * Sleep with the spinlock held (yeh, yeh, I know!),
	 * so that main thread spins a bit.
	 */
	sleep(2);

	/* Release spinlock. */
	assert(pthread_spin_unlock(&lock) == 0);

	pthread_exit(NULL);
}
