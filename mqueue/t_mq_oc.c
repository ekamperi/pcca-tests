#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MQNAME	"/tmqoc"

int main(void)
{
	mqd_t md;

	/* Create a message queue for write only with default parameters. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0777, NULL);
	assert(md != -1);

	/* Disassociate with message queue. */
	assert(mq_close(md) != -1);

	return (EXIT_SUCCESS);
}
