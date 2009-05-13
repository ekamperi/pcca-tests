#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define	MQNAME	"/t_mq_send"
#ifndef MQ_PRIO_MAX
#define MQ_PRIO_MAX	32768	/* XXX: linux specific */
#endif

int main(void)
{
	struct mq_attr attr;
	mqd_t md;
       	int rv;

	/* Invalid message queue descriptor. */
	rv = mq_send(-1, "", 0, 0);
	assert (rv == -1 && errno == EBADF);

	/* Priority is out of range (0...MQ_PRIO_MAX-1) */
	md = mq_open(MQNAME, O_CREAT | O_WRONLY, 0700, NULL); 
	assert(md != -1);

	rv = mq_send(md, "foo", sizeof("foo"), 2*MQ_PRIO_MAX);
	assert(rv == -1 && errno == EINVAL);

	mq_close(md);

	/* Message size is larger than maximum allowed message size */
	/* attr.mq_flags = ? */
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = 1;
	md = mq_open(MQNAME, O_CREAT | O_WRONLY, 0700, &attr);
	assert(md != -1);

	char *p;
	rv = mq_send(md, p, 10, /* priority */ 0);
	assert(rv == -1 && errno == EMSGSIZE);

	mq_close(md);

	printf("passed\n");
}
