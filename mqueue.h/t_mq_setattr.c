#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset */

#define	MQNAME	"/tmqsa"

int main(void)
{
	struct mq_attr attr, oldattr;
	mqd_t md;

	/* Invalid message queue descriptor. */
	assert(mq_setattr(-1, &attr, NULL) == -1 && errno == EBADF);

	/* mq_setattr() and mq_getattr() must report the same exact values. */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 10;	/* Maximum number of messages. */
	attr.mq_msgsize = 1024;	/* Maximum message size. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDWR, 0700, &attr);
	assert(md != -1);

	assert(mq_getattr(md, &oldattr) != -1);
	assert(oldattr.mq_maxmsg == attr.mq_maxmsg);
	assert(oldattr.mq_msgsize == attr.mq_msgsize);
	assert(oldattr.mq_curmsgs == 0 && attr.mq_curmsgs == 0);

	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
