#include <assert.h>
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/* Invalid message queue descriptor. */
	assert(mq_close(-1) == -1 && errno == EBADF);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
