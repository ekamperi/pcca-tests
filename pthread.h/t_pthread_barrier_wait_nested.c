#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N1	60	/* We need a vast number of level-1 threads in
			   order to increase the possibility of catching
			   potential barrier violation.  */

#define N2	5

pthread_barrier_t pb1;	/* level-1 barrier */
pthread_barrier_t pb2;	/* level-2 barrier */

pthread_mutex_t mtx_lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_lock2 = PTHREAD_MUTEX_INITIALIZER;

int checkpoint1 = 0;
int checkpoint2 = 0;

/* Function prototypes. */
static void *thread1(void *);	/* level-1 thread */
static void *thread2(void *);	/* level-2 thread */

int main(void)
{
	pthread_t thpool[N1];
	int i;

	/* Initialize level-1 and level-2 barriers. */
	assert(pthread_barrier_init(&pb1, NULL, N1) == 0);
	assert(pthread_barrier_init(&pb2, NULL, N1 * N2) == 0);

	/* Create level-1 threads. */
	for (i = 0; i < N1; i++) {
		/*
		 * Make sure that there is no thread that cheats and crosses the
		 * barrier, before other threads have reached it as well.
		 * Normally, we wouldn't need a lock around `checkpoint1',
		 * because all threads are supposed to block before they will try
		 * to access it.
		 */
		pthread_mutex_lock(&mtx_lock1);
		assert(checkpoint1 == 0);
		pthread_mutex_unlock(&mtx_lock1);

		assert(pthread_create(&thpool[i], NULL, thread1, (void *)NULL)
		    == 0);
	}

	/* Wait for level-1 threads to complete. */
	for (i = 0; i < N1; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	/* There is no need for a lock now. */
	assert(checkpoint1 == N1);
	assert(checkpoint2 == N1 * N2);

	/* Destroy level-1 and level-2 barriers. */
	assert(pthread_barrier_destroy(&pb1) == 0);
	assert(pthread_barrier_destroy(&pb2) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread1(void *arg)
{
	pthread_t thpool[N2];
	int i, rv;

	/* This will block us. */
	rv = pthread_barrier_wait(&pb1);
	assert(rv == 0 || rv == PTHREAD_BARRIER_SERIAL_THREAD);

	/* At this point all level-1 threads are unleashed! */
	pthread_mutex_lock(&mtx_lock1);
	checkpoint1++;
	pthread_mutex_unlock(&mtx_lock1);

	/* Create level-2 threads. */
	for (i = 0; i < N2; i++) {
                pthread_mutex_lock(&mtx_lock2);
                assert(checkpoint2 == 0);
                pthread_mutex_unlock(&mtx_lock2);

                assert(pthread_create(&thpool[i], NULL, thread2, (void *)NULL)
                    == 0);
        }

	/* Wait for level-2 threads to complete. */
	for (i = 0; i < N2; i++)
		assert(pthread_join(thpool[i], NULL) == 0);

	pthread_exit(NULL);
}

static void *
thread2(void *arg)
{
        int rv;

        /* This will block us. */
        rv = pthread_barrier_wait(&pb2);
        assert(rv == 0 || rv == PTHREAD_BARRIER_SERIAL_THREAD);

        /* At this point all level-2 threads are unleashed! */
        pthread_mutex_lock(&mtx_lock2);
        checkpoint2++;
        pthread_mutex_unlock(&mtx_lock2);

	pthread_exit(NULL);
}
