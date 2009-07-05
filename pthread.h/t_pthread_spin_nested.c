#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	/* for sleep(3) */

#define NTHREADS	10

pthread_spinlock_t lock1;	/* level-1 lock */
pthread_spinlock_t lock2;	/* level-2 lock */

/* Function prototypes. */
static void *thread1(void *);
static void *thread2(void *);

int cnt1 = 0;
int cnt2 = 0;

int main(void)
{
	pthread_t thpool[NTHREADS];
	size_t i;

	/* Initialize level-1 spinlock. */
	assert(pthread_spin_init(&lock1, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Acquire level-1 spinlock. */
	assert(pthread_spin_lock(&lock1) == 0);

	/* Create level-1 threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&thpool[i], NULL, thread1, (void *)NULL)
		    == 0);

	/* Sleep so that level-1 threads spin a bit. */
	sleep(1);

	/* Enough is enough -- release level-1 spinlock. */
	assert(pthread_spin_unlock(&lock1) == 0);

	/*
	 * Wait for level-1 threads to complete.
	 * Each level-1 thread acquires the level-1 spinlock, so the rest will
	 * spin again a bit.
	 */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Destroy level-1 spinlock. */
	assert(pthread_spin_destroy(&lock1) == 0);

	/* Make sure that `NTHREADS' level-1 threads ran. */
	assert(cnt1 == NTHREADS);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread1(void *arg)
{
	pthread_t thpool[NTHREADS];
	size_t i;

        /* Acquire level-1 spinlock. */
        assert(pthread_spin_lock(&lock1) == 0);

	cnt1++;
	cnt2 = 0;

	/* Initialize level-2 spinlock. */
	assert(pthread_spin_init(&lock2, PTHREAD_PROCESS_PRIVATE) == 0);

	/* Create level-2 threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&thpool[i], NULL, thread2, (void *)NULL)
		    == 0);

	/*
	 * Wait for level-2 threads to complete.
	 * Each level-2 thread acquires the level-2 spinlock, so the rest will
	 * spin again a bit.
	 */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* Release level-2 spinlock. */
	assert(pthread_spin_unlock(&lock2) == 0);

	/* Destroy level-2 spinlock. */
	assert(pthread_spin_destroy(&lock2) == 0);

	/* Release level-1 spinlock. */
	assert(pthread_spin_unlock(&lock1) == 0);

        /* Make sure that `NTHREADS' level-2 threads ran. */
        assert(cnt2 == NTHREADS);

	pthread_exit(NULL);
}


static void *
thread2(void *arg)
{
	/* Acquire level-2 spinlock. */
	assert(pthread_spin_lock(&lock2) == 0);

	cnt2++;

	/* Release level-2 spinlock. */
	assert(pthread_spin_unlock(&lock2) == 0);

	pthread_exit(NULL);
}
