#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Function prototypes. */
static void *thread1(void *);
static void *thread2(void *);

int main(void)
{
	pthread_t th1, th2;
	int rv;

	/* Nice value must propagate to all system scope threads in the process. */
	errno = 0;
	rv = nice(2);
	assert(rv != -1 || errno == 0);

	/* Create threads. */
	assert(pthread_create(&th1, NULL, thread1,
		(void *)&rv) == 0);
	assert(pthread_create(&th2, NULL, thread2,
		(void *)&rv) == 0);

	/* Wait for threads to complete. */
	assert(pthread_join(th1, NULL) == 0);
	assert(pthread_join(th2, NULL) == 0);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
thread1(void *arg)
{
	int rv, rv2;

	/* Retrieve nice value from main thread. */
	rv = *(int *)arg;

	errno = 0;
	rv2 = nice(0);
	assert(rv2 != -1 || errno == 0);
	assert(rv2 == rv);

	pthread_exit(NULL);
}

static void *
thread2(void *arg)
{
	int rv, rv2;

        /* Retrieve nice value from main thread. */
        rv = *(int *)arg;

	errno = 0;
        rv2 = nice(0);
        assert(rv2 != -1 || errno == 0);
        assert(rv2 == rv);

	pthread_exit(NULL);
}

