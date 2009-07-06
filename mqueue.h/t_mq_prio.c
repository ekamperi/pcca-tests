#include <assert.h>
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define	MQNAME	"/tmqqprio"

mqd_t md;

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	const char lowmsg[] = "Parent says hello";
	const char highmsg[] = "Parent asks for HELP";
	unsigned int prio;
	int rv;
	pid_t pid;

	signal(SIGABRT, myhandler);

	/* Create a message queue for write only with default parameters. */
	md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
	assert (md != -1);

	/* Send messages, low first, then high. */
	rv = mq_send(md, lowmsg, sizeof(lowmsg), /* priority */ 0);
	assert(rv != -1);

	rv = mq_send(md, highmsg, sizeof(highmsg), /* priority */ 1);
	assert(rv != -1);

	/* Disassociate with message queue. */
	rv = mq_close(md);
	assert(rv != -1);

	/* Fork and have child read the message from parent. */
	pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		/* We are inside the child. */
		md = mq_open(MQNAME, O_RDONLY);
		assert(md != -1);

		char msg_recvd[8192];	/* Implementation defined. */
		rv = mq_receive(md, msg_recvd, sizeof(msg_recvd), &prio);
		assert(rv != -1);
		/*
		 * Make sure that the message with higher priority,
		 * is delivered first of all.
		 */
		assert(strcmp(msg_recvd, highmsg) == 0 && prio == 1);

		rv = mq_receive(md, msg_recvd, sizeof(msg_recvd), &prio);
		assert(rv != -1);
		assert(strcmp(msg_recvd, lowmsg) == 0 && prio == 0);

		/* Disassociate with message queue. */
		rv = mq_close(md);
		assert(rv != -1);

		/* Remove the message queue from the system. */
		rv = mq_unlink(MQNAME);
		assert(rv != -1);

		printf("passed\n");
	} else {
		/* We are inside the parent. */
		int status;
		assert(wait(&status) == pid);
	}

	return EXIT_SUCCESS;
}

static void
myhandler(int sig)
{
	/*
	 * Message queues' name & resources are persistent, i.e., they live
	 * even after the process dies. That's why, disassociate and destroy
	 * the queue on failure, or else we might end up with zombie queues and
	 * hit the limit of max open queues.
	 * Also, we don't care about the return value of the following calls.
	 */
	mq_close(md);
	mq_unlink(MQNAME);

	/* After this, the program will abort. */
}
