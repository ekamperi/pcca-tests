#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memset() */

#define	MQNAME	"/t_mq_open1"
#define	PATH_MAX 1024	/* XXX */

int main(void)
{
	mqd_t md;

	/* O_CREAT is not set and the named mqueue doesn't exist. */
	md = mq_open("nonexistentmqueuename", O_WRONLY, 0700, NULL);
	assert (md == -1 && errno == ENOENT);

	/* Pathname is too long. */
	char *pathname = malloc(2 * PATH_MAX);
	assert(pathname != NULL);
	memset(pathname, 0xff, 2 * PATH_MAX);	/* Make sure we don't terminate prematurely. */

	md = mq_open(pathname, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md == -1 && errno == ENAMETOOLONG);
	free(pathname);

	/* Name already exists and O_CREAT, O_EXCL are both set. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != -1);

	assert(mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL) == -1 && errno == EEXIST);
	mq_close(md);
	mq_unlink(MQNAME);

	/* Try to open a read only message queue for write. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_RDONLY, 0700, NULL);
	assert(md != -1);

	assert(mq_open(MQNAME, O_RDWR) == -1 && errno == EACCES);
	mq_close(md);
	mq_unlink(MQNAME);

	printf("passed\n");

	return (EXIT_SUCCESS);
}
