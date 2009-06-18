#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS	20
#define NITER		20

/* Function prototypes. */
void *parent(void *arg);
void *child(void *arg);

int main(void)
{
	pthread_t thpool[NTHREADS];
	size_t i;

	/* Create parent threads. */
	for (i = 0; i < NTHREADS; i++)
                assert(pthread_create(&thpool[i], NULL, parent,
			   (void *)NULL) == 0);

	/* Wait for parent threads to complete. */
        for (i = 0; i < NTHREADS; i++)
                assert(pthread_join(thpool[i], NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

void *parent(void *arg)
{
	pthread_t thpool[NTHREADS];
	sem_t mysem;
	size_t i;

	/* Initialize semaphore. */
        assert(sem_init(&mysem,
                   0 /* not shared between processes */,
                   NTHREADS/2 /* semaphore value */) == 0);

        /* Create children threads. */
        for (i = 0; i < NTHREADS; i++)
                assert(pthread_create(&thpool[i], NULL, child,
                           (void *)&mysem) == 0);

        /* Wait for children threads to complete. */
        for (i = 0; i < NTHREADS; i++)
                assert(pthread_join(thpool[i], NULL) == 0);

	/* Destroy semaphore. */
	assert(sem_destroy(&mysem) == 0);

	pthread_exit(NULL);
}

void *child(void *arg)
{
	sem_t mysem;
	size_t i;

	/* Retrieve semaphore. */
	mysem = *(sem_t *)arg;

	for (i = 0; i < NITER; i++) {
		assert(sem_wait(&mysem) == 0);
		assert(sem_post(&mysem) == 0);
	}

	pthread_exit(NULL);
}
