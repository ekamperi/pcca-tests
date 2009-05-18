#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

#define	MQNAME	"/tmqts"

int main(void)
{
	struct mq_attr attr;
	mqd_t md;
	int rv;

	/* Create a message queue for write only with default parameters. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != -1);

	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
