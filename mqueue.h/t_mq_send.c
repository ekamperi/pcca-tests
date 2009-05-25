#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

#define	MQNAME	"/tmqssdasdaasd"
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
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != 1);

	rv = mq_send(md, "foo", sizeof("foo"), 2*MQ_PRIO_MAX);
	assert(rv == -1 && errno == EINVAL);

	mq_close(md);
	mq_unlink(MQNAME);

	/*
	 * Message size is larger than maximum allowed message size.
	 * The latter is implementation defined. In NetBSD happens to
	 * be 16*1024 as defined in sys/mqueue.h and kern/sys_mqueue.c.
	 * We use a "sufficiently" large value to cover other
	 * implemenetations as well.
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != -1);

	char *p;
	rv = mq_send(md, p, 32768, /* priority */ 0);
	assert(rv == -1 && errno == EMSGSIZE);

	mq_close(md);
	mq_unlink(MQNAME);

	/* Same as previous but use a non-default maximum message size. */
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 1;	/* Maximum number of messages. */
	attr.mq_msgsize = 50;	/* Maximum message size. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, &attr);
	assert(md != -1);

	p = malloc(2 * attr.mq_msgsize);
	assert(p != NULL);
	memset(p, 0xff, 2 * attr.mq_msgsize);	/* Make sure we don't terminate prematurely */

	rv = mq_send(md, p, 2 * attr.mq_msgsize, /* priority */ 0);
	assert(rv == -1 && errno == EMSGSIZE);

	free(p);

	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
