#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The following macro is equivalent to dynamic initialization by a call to
 * pthread_cond_init() with parameter attr specified as NULL. Mind that no
 * error checks are performed. Also, since the variable is _statically
 * allocated_ we shouldn't (nor we could) call pthread_cond_destroy() on it.
 */
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

int main(void)
{
	pthread_cond_t cond2;

	/* Create a condition variable with default attributes. */
	assert(pthread_cond_init(&cond2, NULL) == 0);

	/* Destroy it. */
	assert(pthread_cond_destroy(&cond2) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
