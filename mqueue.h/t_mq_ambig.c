#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MQNAME	"/t_mq_ambig"

int main(void)
{
	char buf[100];
	mqd_t md;

	/*
	 * In the creation of a message queue, there is an ambiguity between
	 * `oflag' and `mode_t' with respect to which one of them takes
	 * precedence over the other.
	 *
	 * It seems that `oflag' is checked first and then `mode_t'.
	 */

	/*
	 * Create a READ only message queue, but with WRITE permission bits
	 * set, and then try to actually WRITE (i.e., mq_send() data to it).
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDONLY, 0777, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_send(md, buf, sizeof(buf), /* priority */ 0) == -1
	    && errno == EBADF);

	/* Close and remove the message queue. */
	assert(mq_close(md) != (mqd_t)-1);
	assert(mq_unlink(MQNAME) != (mqd_t)-1);

	/*
	 * Create a WRITE only message queue, but with READ permission bits
	 * set, and then try to actually READ (i.e., mq_receive() data from it).
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0777, NULL);
	assert(md != (mqd_t)-1);

	assert(mq_receive(md, buf, sizeof(buf), /* priority */ 0) == -1
	    && errno == EBADF);

	/* Close and remove the message queue. */
	assert(mq_close(md) != (mqd_t)-1);
	assert(mq_unlink(MQNAME) != (mqd_t)-1);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
