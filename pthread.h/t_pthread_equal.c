#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes. */
static void *thread(void *);

int main(void)
{
	pthread_t tid1, tid2;

	/* Create threads. */
	assert(pthread_create(&tid1, NULL, thread, (void *)NULL) == 0);
	assert(pthread_create(&tid2, NULL, thread, (void *)NULL) == 0);

	/* Compare thread IDs. */
	assert(pthread_equal(tid1, tid2) == 0);
	assert(pthread_equal(tid1, tid1) != 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread(void *arg)
{
	pthread_exit(NULL);
}
