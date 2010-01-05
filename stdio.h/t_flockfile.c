#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int wasblocked = 1;

/* Function prototypes. */
static void *mythread(void *arg);

int
main(void)
{
	/*
	 * Open file and associate a FILE* object with it.
	 */
	FILE *fp;
	fp = fopen("sandbox/file777", "r");
	assert(fp != NULL);

	/*
	 * If the lock count is zero or positive and the caller owns the FILE*
	 * object, the count shall be incremented (i.e., the caller shall not
	 * be blocked).
	 */
	size_t i;
	for (i = 0; i < 1000; i++)
		flockfile(fp);

	/*
	 * Create a new thread and let it try acquire the lock.
	 */
	pthread_t tid;
	assert(pthread_create(&tid, NULL, mythread, (void *)fp) == 0);

	/*
	 * Sleep a bit, holding the locks on FILE*, so that the thread will
	 * fail/be blocked when it will attempt to acquire the lock.
	 */
	assert(wasblocked == 1);
	sleep(1);

	/* Release the locks. */
	for (i = 0; i < 1000; i++)
		funlockfile(fp);

	/* Wait for thread to complete. */
	assert(pthread_join(tid, NULL) == 0);
	assert(wasblocked == 0);

	/* Close file -- we are done. */
	assert(fclose(fp) != EOF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}

static void *
mythread(void *arg)
{
	/* Extract the FILE* object */
	FILE *fp = (FILE *)arg;

	/*
	 * Attempt to acquire the lock.
	 * At this point the lock is 1000times acquired by the main thread.
	 * Therefore we shouldn't succeed.
	 */
	assert(ftrylockfile(fp) != 0);

	/* Try again but this time, we will be blocked. */
	flockfile(fp);
	wasblocked = 0;
	funlockfile(fp);

	pthread_exit(NULL);
}
