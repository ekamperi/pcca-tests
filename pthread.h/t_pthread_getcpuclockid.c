#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	pthread_t tid;
	clockid_t clockid;

	/* Retrieve thread ID. */
	tid = pthread_self();

	/* Retrieve clock ID. */
	assert(pthread_getcpuclockid(tid, &clockid) == 0);

	/* XXX: Is there any default value ? */

	printf("passed\n");

	return (EXIT_SUCCESS);
}
