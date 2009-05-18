#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */

#include <sys/types.h>
#include <sys/wait.h>

#define	MQNAME	"/tmqpmc2"

mqd_t md;

static void diep(const char *s);

int main(void)
{
	/* Parent recites a poem. */
	const char *msg[] = { "But I, being poor, have only my dreams;",
			      "I have spread my dreams under your feet;",
			      "Tread softly because you tread on my",
			      "dreams.",
			      "W.B. Yeats" };
	size_t i;
	int rv;
	pid_t pid;

	/*
	 * Create a message queue
	 * Write only and non-block mode with default parameters.
	 */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_NONBLOCK | O_WRONLY,
		     0700, NULL);
	if (md == -1)
		diep("mq_open");

	/* Send messages. */
	for (i = 0; i < sizeof(msg) / sizeof(msg[0]); i++) {
		rv = mq_send(md, msg[i], strlen(msg[i]) + 1, /* priority */ 0);
		if (rv == -1)
			diep("mq_send");
	}

	/* Disassociate with message queue. */
	rv = mq_close(md);
	if (rv == -1)
		diep("mq_close");

	/* Fork and have child read the message from parent. */
	pid = fork();
	if (pid == -1) {
		diep("fork");
	} else if (pid == 0) {
		/* We are inside the child. */
		md = mq_open(MQNAME, O_RDONLY);
		if (md == -1)
			diep("child: mq_open");

		char msg_recvd[8192];	/* Implementation defined. */
		for (i = 0; ; i++) {
			rv = mq_receive(md, msg_recvd, sizeof(msg_recvd), NULL);
			if (rv == -1) {
				if (errno == EAGAIN)
					break;
				else
					diep("child: mq_receive");

			}

			/*printf("%s\n", msg_recvd);*/
			assert(strcmp(msg_recvd, msg[i]) == 0);
		}

		/* Disassociate with message queue. */
		rv = mq_close(md);
		if (rv == -1)
			diep("child: mq_close");

		/* Remove the message queue from the system. */
		rv = mq_unlink(MQNAME);
		if (rv == -1)
			diep("mq_unlink");

		printf("passed\n");
	} else {
		/* We are inside the parent. */
		int status;
		wait(&status);
	}

	return EXIT_SUCCESS;
}

static void
diep(const char *s)
{
	perror(s);

	/*
	 * Message queues' name & resources are persistent, i.e., they live
	 * even after the process dies. That's why, disassociate and destroy
	 * the queue on failure, or else we might end up with zombie queues and
	 * hit the limit of max open queues.
	 * Also, we don't care about the return value of the following calls.
	 */
	mq_close(md);
	mq_unlink(MQNAME);

	exit(EXIT_FAILURE);
}
