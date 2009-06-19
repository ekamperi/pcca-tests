#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>	/* fork() */
#include <sys/wait.h>

#define	MQNAME	"/tmqpcmp"
#define NMESSAGES 200

mqd_t md, md2;

/* Function prototypes. */
static void myhandler(int sig);

int main(void)
{
	size_t i;
	int rv;
	pid_t pid;

	signal(SIGABRT, myhandler);

	/* Fork and let the game begin. */
	pid = fork();
	assert(pid != -1);

	if (pid != 0) {
		/* We are inside the parent. */
		char buf[100];

		/* Create a message queue for write only with default parameters. */
		md = mq_open(MQNAME, O_CREAT | O_EXCL | O_WRONLY, 0700, NULL);
		assert (md != -1);

		for (i = 0; i < NMESSAGES; i++) {
			snprintf(buf, sizeof(buf), "%d\n", i);

			/* Send messages with increasing priority. */
			rv = mq_send(md, buf, sizeof(buf),
			    /* priority */ i);
			assert(rv != -1);
		}

		/* Disassociate with message queue. */
		rv = mq_close(md);
		assert(rv != -1);

		/* Wait until child has read all messages. */
		int status;
		wait(&status);

                /* Remove the message queue from the system. */
                rv = mq_unlink(MQNAME);
                assert(rv != -1);

                printf("passed\n");
	} else {
		/* We are inside the child. */
		char msg_recvd[8192];   /* Implementation defined. */
		unsigned int oldprio = UINT_MAX, prio, priostr;

		/* Give parent some time to open the queue. */
		usleep(10000);

		/* We are inside the child. */
		md2 = mq_open(MQNAME, O_RDONLY);
		assert(md2 != -1);

		for (i = 0; i < NMESSAGES; i++) {
			rv = mq_receive(md2, msg_recvd, sizeof(msg_recvd),
			    &prio);
			assert(rv != -1);

			printf("%s\n", msg_recvd);
			fflush(NULL);

			priostr = atoi(msg_recvd);
			printf("%d\n", priostr);
			assert(priostr == prio);

			//printf("prio = %d\toldprio = %d\n", prio, oldprio);
			assert(prio < oldprio);
			oldprio = prio;

			//printf("prio = %d\tpriostr = %d\toldprio = %d\n",
			//prio, priostr, oldprio);
		}

		/* Disassociate with message queue. */
		rv = mq_close(md2);
		assert(rv != -1);
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
	mq_close(md2);
	mq_unlink(MQNAME);

	/* After this, the program will abort. */
}
