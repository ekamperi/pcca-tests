#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	N	1000000	/* Number of items to sort */

/* Function prototypes. */
int mycmp(const void *, const void *);

int main(void)
{
	int a[N];
	size_t i;

	/* Initialize random number generator. */
	srand(time(NULL));

	/* Generate some (not so) random numbers. */
	for (i = 0; i < N; i++)
		a[i] = rand();

	/* Sort the array. */
	qsort(a, N, sizeof(*a), mycmp);

	/* Validate the results. */
	for (i = 1; i < N; i++)
		assert(a[i] >= a[i-1]);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

int
mycmp(const void *px, const void *py)
{
	int x = *(const int *)px;
	int y = *(const int *)py;

	return (x - y);
}
