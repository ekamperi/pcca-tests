#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */
#include <time.h>

#define	MQNAME	"/tmqts2"

int main(void)
{
	struct mq_attr attr;
	struct timespec abs_timeout;
	mqd_t md;

	/*
	 * Create a message queue for write only with capacity `1'
	 * (we want to emulate a full queue).
	 */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages */
	attr.mq_msgsize = 1024;	/* Maximum message size */

	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != -1);

	/* */
	assert(mq_send(md, "foo", sizeof("foo"), /* priority */ 0) != -1);

	/* */
	abs_timeout.tv_sec = 0;
	abs_timeout.tv_nsec = 0;

	/* */
	assert(mq_timedsend(md, "foo", sizeof("foo"),
			    /* priority */ 0,
			    &abs_timeout) == -1 && errno == ETIMEDOUT);

	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
