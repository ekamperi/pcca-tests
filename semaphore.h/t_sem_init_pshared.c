#include <assert.h>
#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	sem_t mysem;
	pid_t pid;

	/* Create a semaphore. */
	assert(sem_init(&mysem,
		   1 /* shared between processes */,
		   1 /* semaphore value */) == 0);

	/* Fork. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		assert(sem_wait(&mysem) == 0);
		assert(sem_post(&mysem) == 0);

		/* Wait for child to complete. */
		int status;
		assert(wait(&status) == pid);

		/* Destroy semaphore. */
		assert(sem_destroy(&mysem) == 0);

		printf("passed\n");
	} else {
		/* We are inside the child. */
		assert(sem_wait(&mysem) == 0);
                assert(sem_post(&mysem) == 0);
	}

	return (EXIT_SUCCESS);
}
