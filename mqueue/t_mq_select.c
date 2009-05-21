#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>	/* fork() */

#define MQNAME	"/2tam"

int main(void)
{
	const char msg[] = "Child says hello to parent";
	struct timeval abs_timeout;
	mqd_t md;
	fd_set ms;
	pid_t pid;

	/* Create a message queue for write only with default parameters. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert(md != -1);

	/* Initialize descriptor set to null set. */
	FD_ZERO(&ms);

	/* Add message queue descriptor to set. */
	FD_SET(md, &ms);
	assert(FD_ISSET(md, &ms));	/* Just a sanity check. */

	/* Wait for 1 second. */
	abs_timeout.tv_sec = 1;
	abs_timeout.tv_usec = 0;

	/* This should time out. */
	assert(select(md + 1, &ms, NULL, NULL, &abs_timeout) == 0);

	/* Fork. */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		/* Wait for parent to block on select(). */
		sleep(1);

		/* Send message. */
		assert(mq_send(md, msg, sizeof(msg), /* priority */ 0) != -1);
	} else {
		/* We are inside the parent. */
		assert(select(md + 1, &ms, NULL, NULL, &abs_timeout) == 1);
		assert(FD_ISSET(md, &ms));

		char msg_recvd[8192];	/* Implementation defined. */
		assert(mq_receive(md, msg_recvd, sizeof(msg_recvd), NULL) != -1);
		assert(strcmp(msg_recvd, msg) == 0);

		/* Remove message queue descriptor from the set. */
		FD_CLR(md, &ms);

		/*
		 * At this point we know for sure that the child has completed,
		 * otherwise we would still be blocked by select().
		 */

		/* Disassociate with message queue. */
		mq_close(md);

		/* Remove the message queue from the system. */
		mq_unlink(MQNAME);

		printf("passed\n");
	}

	return (EXIT_SUCCESS);
}
