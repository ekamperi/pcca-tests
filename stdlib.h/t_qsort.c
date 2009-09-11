#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NTHREADS	10	/* Number of threads to spawn */
#define	NITEMS		100000	/* Number of items to sort (per thread) */

/* Function prototypes. */
static void *thrfun(void *);
static int mycmp(const void *, const void *);

int main(void)
{
	pthread_t tid[NTHREADS];
	size_t i;

	/* Initialize random number generator. */
	srand(time(NULL));

	/* Create the threads. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_create(&tid[i], NULL, thrfun, NULL) == 0);

	/* Wait for the threads to complete. */
	for (i = 0; i < NTHREADS; i++)
		assert(pthread_join(tid[i], NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thrfun(void *arg)
{
	int a[NITEMS];
	size_t i;

	/* Generate some (not so) random numbers. */
	for (i = 0; i < NITEMS; i++)
		a[i] = rand();

	/* Sort the array. */
	qsort(a, NITEMS, sizeof(*a), mycmp);

	/* Validate the results. */
	for (i = 1; i < NITEMS; i++)
		assert(a[i] >= a[i-1]);

	pthread_exit(NULL);
}

static int
mycmp(const void *px, const void *py)
{
	int x = *(const int *)px;
	int y = *(const int *)py;

	return (x - y);
}
