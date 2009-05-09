#include <assert.h>
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#define	MQNAME	"/t_mq_open"
#define	PATH_MAX 1024	/* XXX */


int main(void)
{
	mqd_t md;
       	int rv;

	/* invalid mqueue name */
	md = mq_open("", O_CREAT | O_WRONLY, 0700, NULL);
	assert (md == -1 && errno == EINVAL);

	/* O_CREAT is not set and the named mqueue doesn't exist */
	md = mq_open("nonexistentmqueuename", O_WRONLY, 0700, NULL);
	/*assert (md == -1 && errno == EINVAL);*/

	/* pathname is too long */
	char *pathname = malloc(2 * PATH_MAX);
	assert(pathname != NULL);

	md = mq_open(pathname, O_CREAT | O_WRONLY, 0700, NULL);
	assert(md == -1 && errno == ENAMETOOLONG);
	free(pathname);

}
