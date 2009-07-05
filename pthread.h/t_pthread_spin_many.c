#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for sleep(3) */

#define NTHREADS	100

pthread_spinlock_t lock;
int cnt1 = 0;
int cnt2 = 0;

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t thpool[NTHREADS];
	size_t i;

	/* Initialize spinlock. */
	assert(pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE) == 0);

        /* Acquire spinlock. */
        assert(pthread_spin_lock(&lock) == 0);

	/* Create threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&thpool[i], NULL, thread, (void *)NULL)
		    == 0);

	/* Sleep so that the threads spin a bit. */
	sleep(1);

	/* Enough is enough -- release spinlock. */
	assert(pthread_spin_unlock(&lock) == 0);

	/*
	 * Wait for threads to complete.
	 * Each thread acquires the spinlock, so the rest will
	 * spin again a bit.
	 */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Destroy spinlock. */
	assert(pthread_spin_destroy(&lock) == 0);

	/* Make sure that NTHREADS were ran. */
	assert(cnt1 == NTHREADS);
	assert(cnt2 == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	/* Acquire spinlock. */
	assert(pthread_spin_lock(&lock) == 0);

	/* Increase monotonically. */
	cnt1++;

	/* Counter must always be 0. */
	assert(cnt2 == 0);

	cnt2++;
	cnt2--;

	assert(cnt2 == 0);

	/* ... and immediately release it. */
	assert(pthread_spin_unlock(&lock) == 0);

	pthread_exit(NULL);
}
